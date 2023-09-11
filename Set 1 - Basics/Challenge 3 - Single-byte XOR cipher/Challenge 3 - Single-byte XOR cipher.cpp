///////////////////////////////////////////////////////////////////////////////
// Cryptopals Challenges
// Set 1: Basics
// Challenge 3 - Single-byte XOR cipher
// 9/11/2023
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cout;
using std::endl;
#include <map>
using std::map;

#define ALPHABET_LENGTH 26

//https://mathcenter.oxford.emory.edu/site/math125/englishLetterFreqs/
static map<char, double> charFrequency = { {'e', 12.702}, {'t', 9.056}, {'a', 8.167}, {'o', 7.507}, {'i', 6.966}, {'n', 6.749},
                                          {'s', 6.327},{'h', 6.094}, {'r', 5.987}, {'d', 4.253}, {'l', 4.025}, {'c', 2.782},
                                          {'u', 2.758}, {'m', 2.406}, {'w', 2.360}, {'f', 2.228}, {'g', 2.015}, {'y', 1.974},
                                          {'p', 1.929}, {'b', 1.492}, {'v', 0.978}, {'k', 0.772}, {'j', 0.153}, {'x', 0.150},
                                          {'q', 0.095}, {'z', 0.074} };
static map<char, double> textCharFrequency = {};
static const char *const alphabet = "abcdefghijklmnopqrstuvwxyz";

char findCipherKey(char *encodedString, unsigned int encodedStrLength, char *&decodedString);
void convertHexToString(char *hexString, char *charStr);
void calculateCharacterFrequencies();
float computeFittingQuotient(char *encodedStr, char *key);
void decipher(char key, char *decodedStr);

int main()
{
    char encodedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    unsigned int encodedStrLength = sizeof(encodedString) / sizeof(char) - 1;

    char *decodedString;
    char key = findCipherKey(encodedString, encodedStrLength, decodedString);
    cout << "Encoded String: " << encodedString << "\nDecoded String: " << decodedString << "\nKey: " << key << endl;
    free(decodedString);

    return 0;
}

/******************************************************************************
* Finds the byte key to decode they cipher text with using XOR.
*
* encodedString - the encoded cipher text
* encodedStrLength - the length of the cipher string once converted from hex to 
*                       ASCII
* decodedString - pointer to where the decoded cipher text will be stored, 
*                   memory must be freed sometime after function call
*
* Returns: the single-byte cipher key used to decode the cipher text.
*
******************************************************************************/
char findCipherKey(char *encodedString, unsigned int encodedStrLength, char *&decodedString)
{
    char key = -1;
    unsigned int asciiStrLength = (encodedStrLength / 2) + 1;

    char *asciiStr = (char *)malloc(asciiStrLength);
    if (asciiStr != nullptr)
    {
        memset(asciiStr, 0, asciiStrLength);

        convertHexToString(encodedString, asciiStr);
        calculateCharacterFrequencies();
        computeFittingQuotient(encodedString, &key);

        decodedString = (char *)malloc(asciiStrLength);
        if (decodedString != nullptr)
        {
            memset(decodedString, 0, asciiStrLength);
            decipher(key, decodedString);
        }

        free(asciiStr);
    }

    return key;
}

/******************************************************************************
* Converts the hex values of the cipher text to ASCII characters.
*
* hexString - the encoded cipher text in hex form
* asciiStr - the encoded cipher text in ASCII form
*
******************************************************************************/
void convertHexToString(char *hexString, char *asciiStr)
{
    //convert the hex string into ASCII and store in asciiStr
}

/******************************************************************************
* Calculates the character frequency of each alphabet character in the cipher
* text and stores the frequency of each character in a map.
*
******************************************************************************/
void calculateCharacterFrequencies()
{
    //calculate the frequency of each letter in the alphabet in the encoded string and store in struct array
}

float computeFittingQuotient(char *encodedStr, char *key)
{
    //use the calculated character frequencies to compute fitting quotient
    return 0;
}

void decipher(char key, char *decodedStr)
{

}
