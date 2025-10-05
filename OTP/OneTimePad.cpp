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

	cout << "M = " << message << " K = " << finalKey << endl;

	string cipherText = e(*m, *k);

	cout << "cipherText = " << cipherText << endl;

	const string* c = &cipherText; 

	string originalMessage = d(*c, *k);

	cout << "originalMessage = " << originalMessage << endl;
}

string e(string m, string k)
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

string d(string c, string k)
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

