///////////////////////////////////////////////////////////////////////////////
// Cryptopals Challenges
// Set 1: Basics
// Challenge 3 - Single-byte XOR cipher
// 9/11/2023
///////////////////////////////////////////////////////////////////////////////
#include <iostream> //remove after done testing
using std::cout;
using std::endl;
#include <cmath>
using std::abs;

#include "Single-byte_XOR.h"

//https://mathcenter.oxford.emory.edu/site/math125/englishLetterFreqs/
static const char *const alphabet = "abcdefghijklmnopqrstuvwxyz";
static const map<char, double> charFrequencies = { {'e', 12.702}, {'t', 9.056}, {'a', 8.167}, {'o', 7.507}, {'i', 6.966}, {'n', 6.749},
                                                 {'s', 6.327}, {'h', 6.094}, {'r', 5.987}, {'d', 4.253}, {'l', 4.025}, {'c', 2.782},
                                                 {'u', 2.758}, {'m', 2.406}, {'w', 2.360}, {'f', 2.228}, {'g', 2.015}, {'y', 1.974},
                                                 {'p', 1.929}, {'b', 1.492}, {'v', 0.978}, {'k', 0.772}, {'j', 0.153}, {'x', 0.150},
                                                 {'q', 0.095}, {'z', 0.074} };
static map<uint8_t, double> keyScores = {};

/******************************************************************************
* Finds the byte key to decode the encrypted text with.
*
* encryptedString - the encrypted text
* encryptedStrLength - the length of the encrypted string once converted from 
*                       hex to ASCII
*
* Returns: the single-byte key used to decrypt the encrypted text.
*
******************************************************************************/
uint8_t findSingleByteXORCipherKey(const char *encryptedString, const int encryptedStrLength)
{
    if(encryptedStrLength < 2) return -1;

    vector<uint8_t> encryptedAsciiChars;
    vector<uint8_t> decryptedAsciiChars;

    convertHexToASCII(encryptedString, encryptedStrLength, &encryptedAsciiChars);
    for(int i = 0; i < POSSIBLE_KEYS; i++) //try each possible key and calculate scores
    {
        if(!decryptedAsciiChars.empty()) decryptedAsciiChars.clear();
        decryptSingleByteXOR(encryptedAsciiChars, decryptedAsciiChars, i);

        //Debug print
        /*cout << "Key: " << i << " ";
        for(int i = 0; i < decryptedAsciiChars.size(); i++)
        {
            cout << decryptedAsciiChars[i];
        }
        cout << endl;*/

        double keyScore = calculateFittingQuotient(decryptedAsciiChars);
        keyScores.insert(std::pair<uint8_t, double>(i, keyScore));
    }

    uint8_t key = getMaxValueKey(keyScores);
    return key;
}

/******************************************************************************
* XORs each character of the encrypted string with a single byte key.
*
* encryptedAsciiChars - vector containing the encrypted string in ASCII form
* decryptedAsciiChars - vector where the decrypted string is to be stored
* key - the byte key used to decrypt the string
*
******************************************************************************/
void decryptSingleByteXOR(vector<uint8_t> &encryptedAsciiChars, vector<uint8_t> &decryptedAsciiChars, const uint8_t key)
{
    for(int i = 0; i < encryptedAsciiChars.size(); i++)
        decryptedAsciiChars.push_back(encryptedAsciiChars[i] ^ key);
}

/******************************************************************************
* XORs each character of the encrypted string with the specified single byte
* key and prints the result with the key used. Meant to be used in testing the
* results of findSingleByteXORCipherKey().
*
* encryptedString - a pointer to the array of characters to be decoded
* encryptedStrLength - the length of the encrypted string
* key - the byte key used to decrypted the string
*
******************************************************************************/
void decryptSingleByteXOR(const char *encryptedString, const int encryptedStrLength, uint8_t key)
{
    vector<uint8_t> encryptedAsciiChars;
    vector<uint8_t> decryptedString;

    convertHexToASCII(encryptedString, encryptedStrLength, &encryptedAsciiChars);
    for(int i = 0; i < encryptedAsciiChars.size(); i++)
        decryptedString.push_back(encryptedAsciiChars[i] ^ key);

    printDecryptionResult(decryptedString, key);
}

/******************************************************************************
* Converts the hex value char to its integer equivalent.
*
* c - the character to be converted to integer equivalent
*
* Returns: the integer equivalent of the char passed in.
*
******************************************************************************/
char hexToIntVal(const char c)
{
    if(c >= '0' && c <= '9') return c - '0';
    if(tolower(c) >= 'a' && tolower(c) <= 'f') return (c - 'a') + 10;
    return -1;
}

/******************************************************************************
* Converts the hex values of the encrypted text into ASCII characters.
*
* hexString - the encrypted text in hex form
* hexStrLength - the length of hexString
* encryptedAsciiChars - the encrypted text in ASCII form
*
******************************************************************************/
void convertHexToASCII(const char *hexString, const int hexStrLength, vector<uint8_t> *encryptedAsciiChars)
{
    for(int i = 0, j = 0; i < hexStrLength - 1; i++, j++)
    {
        uint8_t c = hexToIntVal(hexString[i]);
        encryptedAsciiChars->push_back((c << 4) + hexToIntVal(hexString[++i]));
    }
}

/******************************************************************************
* Calculates the fitting quotient of the decrypted text and returns it.
* 
* decodedAsciiChars - vector containing the decoded ASCII characters
* 
* Returns: The fitting quotient of the current key.
* 
******************************************************************************/
double calculateFittingQuotient(vector<uint8_t> &decodedAsciiChars)
{
    int textLength = decodedAsciiChars.size();
    double numerator = 0;
    for(int i = 0; i < ALPHABET_LENGTH; i++)
    {
        double charFrequency = 0;
        for(int j = 0; j < textLength; j++)
        {
            if(decodedAsciiChars[j] == ' ') numerator += 15;
            if(tolower(decodedAsciiChars[j]) == alphabet[i]) charFrequency++;
        }

        charFrequency /= textLength;
        double letterFreq = charFrequencies.find(alphabet[i])->second;
        numerator += abs(charFrequencies.find(alphabet[i])->second - charFrequency);
    }

    return numerator / ALPHABET_LENGTH;
}

/******************************************************************************
* Finds the best scoring key in map and returns it. Higher score means a better
* match.
*
* valueMap - A map containing key->value pairs of 8-bit keys and their score
*               based on calculated fitting quotient
*
* Returns: The best fitting key to decode the cipher based on its score.
*
******************************************************************************/
uint8_t getMaxValueKey(map<uint8_t, double> &valueMap)
{
    uint8_t key = 0;
    double max = 0;
    for(auto iter = valueMap.begin(); iter != valueMap.end(); iter++)
    {
        if(iter->second > max)
        {
            key = iter->first;
            max = iter->second;
        }
    }

    return key;
}

/******************************************************************************
* Prints the decrypted string and the integer value of the key used.
*
* decryptedString - A vector containing the decrypting string to be printed
* key - the key used to decrypt decryptedString
*
******************************************************************************/
void printDecryptionResult(vector<uint8_t> &decryptedString, uint8_t key)
{
    cout << "Key: " << unsigned(key) << "\nDecrypted String: ";
    for(int i = 0; i < decryptedString.size(); i++)
    {
        cout << decryptedString[i];
    }
    cout << endl;
}