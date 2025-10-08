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
	const string message  = "The is the message";	
	const string message2 = "My password is BigCheese2003";
	string key(max(message.length(), message2.length()), 'x');

	int i = 0;
	while (i < key.length()) 
		key[i++] = rand();

	const string finalKey = key;
	
	//cout << "M = " << message << " K = " << transformKey << endl;

	const string cipherText = encrypt(message, finalKey);

	cout << "cipherText = " << cipherText << endl;

	const string originalMessage = decrypt(cipherText, finalKey);

	cout << "originalMessage = " << originalMessage << endl;
	
	//TWO-TIME-PAD-ATTACK
	const string cipherText2 = encrypt(message2, finalKey);

	cout << "cipherText2 = " << cipherText2 << endl;

	const string ciphersXORedTogether = encrypt(cipherText, cipherText2);

	const string test = decrypt(ciphersXORedTogether, message);
	cout << "TEST  = " << test << endl;

	//const string guess = cribDrag(ciphersXORedTogether, " the ");
	const string guess = decrypt(ciphersXORedTogether, "The ");
	cout << "GUESS = " << guess << endl;
	
	myMap xors = makeASCIIMap();
}

myMap makeASCIIMap()
{
	myMap m;
	for (char c = ' '; c <= '~'; c++)
	{		
		for (char i = c + 1; i <= '~'; i++)
		{	
			const charPair cp (c, i);
			m[c ^ i] = cp;
			//cout << "char c = " << c << " XORed with char " << i << " = " << (c ^ i) << endl;   
		}
	}
	return m;
}

const string encrypt(const string m, const string k)
{
	string stringBinary;
	for (int i = 0; i < m.length(); i++)
		stringBinary += m[i] ^ k[i];
	return stringBinary;
}

const string decrypt(const string c, const string k)
{
	string stringText;
        for (int i = 0; i < c.length(); i++)
                stringText += c[i] ^ k[i];
        return stringText;
}

