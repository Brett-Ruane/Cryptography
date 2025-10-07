#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "OneTimePad.hpp"

using namespace std;

int main(void)
{
	srand(time(0));
	const string message = " the is the message";	
	const string message2 = "my password is password";
	string key(max(message.length(), message2.length()) * 8, 'x');

	int i = 0;
	while (i < key.length()) 
	{
		int randNum = rand() % 2;
		if (randNum == 1)  
			key[i] = '1';
		else 
			key[i] = '0';	
		i++;
	}

	const string finalKey = key;

	string transformKey;
	for (int i = 0; i < key.length() / 8; i++) 
	{
		bitset<8> kBits(key.substr(i*8, i*8+8));
		char ch = static_cast<char>(kBits.to_ulong());
		transformKey += ch;
	} 
	
	//cout << "M = " << message << " K = " << transformKey << endl;

	const string cipherText = e(message, finalKey);

	//cout << "cipherText = " << cipherText << endl;

	const string originalMessage = d(cipherText, finalKey);

	cout << "originalMessage = " << originalMessage << endl;
	
	//TWO-TIME-PAD-ATTACK
	const string cipherText2 = e(message2, finalKey);

	const string ciphersXORedTogether = xorCipherText(cipherText, cipherText2);

	const string test = d(ciphersXORedTogether, expand(message));
	cout << "TEST  = " << test << endl;

	//const string guess = cribDrag(ciphersXORedTogether, " the ");
	const string guess = d(ciphersXORedTogether, expand(" the "));
	cout << "GUESS = " << guess << endl;
}

const string expand(const string str)
{	
	string messageExpand;
	for (int i = 0; i < str.length(); i++)
	{
		bitset<8> add(str[i]);
		messageExpand += add.to_string();
	}
	return messageExpand;
}

const string xorCipherText(const string c1, const string c2)
{	
	string messageXOR;
        for (int i = 0; i < c1.length(); i += 8)
        {
		bitset<8> c1Bits(c1.substr(i, i+8));      
		bitset<8> c2Bits(c2.substr(i, i+8));
		messageXOR += (c1Bits ^ c2Bits).to_string();
	}
	return messageXOR;
}

const string e(const string m, const string k)
{
	string stringBinary;
	for (int i = 0; i < m.length(); i++)
	{
	        bitset<8> mBits(m[i]);
		bitset<8> kBits(k.substr(i*8, i*8+8));       
		//cout << "mBits = " << mBits.to_ulong() << " for char " << m[i] << endl;
		//cout << "kBits = " << kBits << endl;
		stringBinary += (mBits ^ kBits).to_string();
	}
	return stringBinary;	
}

const string d(const string c, const string k)
{
	string stringText;
        for (int i = 0; i < min(c.length(), k.length()); i += 8)
        {
		bitset<8> cBits(c.substr(i, i+8));      
		bitset<8> kBits(k.substr(i, i+8));
		//cout << "cBits = " << cBits << " kBits = " << kBits << " XOR = " << (cBits ^ kBits).to_ulong() << endl;

		char ch = static_cast<char>((cBits ^ kBits).to_ulong());
                stringText += ch;
        }
        return stringText;
}

