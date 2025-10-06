#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include "OneTimePad.hpp"

using namespace std;

int main()
{
	srand(time(0));
	const string message = "this is the message";
	string key(message.length() * 8, 'x');

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
	const string* m = &message;
	const string* k = &finalKey;

	string transformKey;
	for (int i = 0; i < key.length() / 8; i++) 
	{
		bitset<8> kBits(key.substr(i*8, i*8+8));
		char ch = static_cast<char>(kBits.to_ulong());
		transformKey += ch;
	} 
	
	cout << "M = " << message << " K = " << transformKey << endl;

	const string cipherText = e(*m, *k);

	cout << "cipherText = " << cipherText << endl;

	const string* c1 = &cipherText; 

	const string originalMessage = d(*c1, *k);

	cout << "originalMessage = " << originalMessage << endl;
	
	//TWO-TIME-PAD-ATTACK
	const string message2 = "gate an ape birchT";
	const string* m2 = &message2;
	
	const string cipherText2 = e(*m2, *k);
	
	const string* c2 = &cipherText2;

	const string ciphersXORedTogether = xorCipherText(*c1, *c2);
}

//string cribDrag

string xorCipherText(const string c1, const string c2)
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

string e(const string m, const string k)
{
	string stringBinary;
	for (int i = 0; i < m.length(); i++)
	{
	        bitset<8> mBits(m[i]);
		bitset<8> kBits(k.substr(i*8, i*8+8));       
		cout << "mBits = " << mBits.to_ulong() << " for char " << m[i] << endl;
		cout << "kBits = " << kBits << endl;
		stringBinary += (mBits ^ kBits).to_string();
	}
	return stringBinary;	
}

string d(const string c, const string k)
{
	string stringText;
        for (int i = 0; i < c.length(); i += 8)
        {
		bitset<8> cBits(c.substr(i, i+8));      
		bitset<8> kBits(k.substr(i, i+8));
		cout << "cBits = " << cBits << " kBits = " << kBits << " XOR = " << (cBits ^ kBits).to_ulong() << endl;

		char ch = static_cast<char>((cBits ^ kBits).to_ulong());
                stringText += ch;
        }
        return stringText;
}

