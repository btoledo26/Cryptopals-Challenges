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
#define POSSIBLE_KEYS 256

//https://mathcenter.oxford.emory.edu/site/math125/englishLetterFreqs/
static const map<char, double> charFrequency = { {'e', 12.702}, {'t', 9.056}, {'a', 8.167}, {'o', 7.507}, {'i', 6.966}, {'n', 6.749},
                                                 {'s', 6.327}, {'h', 6.094}, {'r', 5.987}, {'d', 4.253}, {'l', 4.025}, {'c', 2.782},
                                                 {'u', 2.758}, {'m', 2.406}, {'w', 2.360}, {'f', 2.228}, {'g', 2.015}, {'y', 1.974},
                                                 {'p', 1.929}, {'b', 1.492}, {'v', 0.978}, {'k', 0.772}, {'j', 0.153}, {'x', 0.150},
                                                 {'q', 0.095}, {'z', 0.074} };
static map<char, double> keyScores = {};
static const char *const alphabet = "abcdefghijklmnopqrstuvwxyz";

unsigned char findCipherKey(const char *encodedString, const unsigned int encodedStrLength, char *&decodedString);
char HexToIntVal(const char c);
void convertHexToASCII(const char *hexString, const unsigned int encodedStrLength, char *charStr);
void decode(const char *encodedAsciiStr, const unsigned int asciiStrLength, const unsigned char key, char *decodedStr);
void calculateCharacterFrequencies(const char *encodedAsciiStr, const unsigned int asciiStrLength);
double computeFittingQuotient(const char *encodedStr, const unsigned char key);

int main()
{
    char encodedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    unsigned int encodedStrLength = sizeof(encodedString) / sizeof(char) - 1;

    char *decodedString = nullptr;
    char key = findCipherKey(encodedString, encodedStrLength, decodedString);

    //TODO: remove need to pass in pointer for decoded string and just decode the string using the returned key after it is found

    cout << "Encoded String: " << encodedString << "\nDecoded String: " << decodedString << "\nKey: " << key << endl;
    free(decodedString);

    return 0;
}

/******************************************************************************
* Finds the byte key to decode the cipher text with.
*
* encodedString - the encoded cipher text
* encodedStrLength - the length of the cipher string once converted from hex to 
*                       ASCII
* decodedString - pointer to where the decoded cipher text will be stored. 
*                   must not be nullptr, and memory must be freed sometime 
                    after function call
*
* Returns: the single-byte cipher key used to decode the cipher text.
*
******************************************************************************/
unsigned char findCipherKey(const char *encodedString, const unsigned int encodedStrLength, char *&decodedString)
{
    char key = -1;
    unsigned int asciiStrLength = (encodedStrLength / 2) + 1;

    char *encodedAsciiStr = (char *)malloc(asciiStrLength);
    if(encodedAsciiStr != nullptr)
    {
        memset(encodedAsciiStr, 0, asciiStrLength);
        convertHexToASCII(encodedString, encodedStrLength, encodedAsciiStr);

        decodedString = (char *)malloc(asciiStrLength);
        if(decodedString != nullptr)
        {
            for(int i = 0; i < POSSIBLE_KEYS; i++) //try each possible key and calculate scores
            {
                memset(decodedString, 0, asciiStrLength);
                decode(encodedAsciiStr, asciiStrLength, i, decodedString);
                double keyScore = computeFittingQuotient(decodedString, i);
                keyScores.insert(std::pair<char, double>(alphabet[i], keyScore));
            }
        }

        //find best scoring key in map and store in key variable

        free(encodedAsciiStr);
    }

    return key;
}

/******************************************************************************
* Converts the hex value char to its integer equivalent.
*
* c - the character to be converted to integer equivalent
*
* Returns: the integer equivalent of the char passed in.
*
******************************************************************************/
char HexToIntVal(const char c)
{
    if(c >= '0' && c <= '9') return c - '0';
    if(tolower(c) >= 'a' && tolower(c) <= 'f') return (c - 'a') + 10;
    return -1;
}

/******************************************************************************
* Converts the hex values of the cipher text into ASCII characters.
*
* hexString - the encoded cipher text in hex form
* hexStrLength - the length of hexString
* encodedAsciiStr - the encoded cipher text in ASCII form
*
******************************************************************************/
void convertHexToASCII(const char *hexString, const unsigned int hexStrLength, char *encodedAsciiStr)
{
    for(int i = 0, j = 0; i < hexStrLength; i++, j++)
    {
        unsigned char c = HexToIntVal(hexString[i]);
        encodedAsciiStr[j] = (c << 4) + HexToIntVal(hexString[++i]);
    }
}

/******************************************************************************
* XORs the encoded string with a single byte key
*
* encodedAsciiStr - the encoded string in ASCII form
* asciiStrLength - the length of encodedAsciiStr
* key - the byte key used to decode the string
* decodedStr - where the decoded string is to be stored
*
******************************************************************************/
void decode(const char *encodedAsciiStr, const unsigned int asciiStrLength, const unsigned char key, char *decodedStr)
{
    for(int i = 0; i < asciiStrLength; i++)
    {
        decodedStr[i] = encodedAsciiStr[i] ^ key;
    }
}

/******************************************************************************
* Calculates the character frequency of each alphabet character in the cipher
* text
* 
*
******************************************************************************/
void calculateCharacterFrequencies(const char *encodedAsciiStr, const unsigned int asciiStrLength)
{
    //calculate the frequency of each letter in the alphabet in the encoded string and store in struct array
    //TODO: Add logic

    for(int i = 0; i < ALPHABET_LENGTH; i++)
    {
        double charFrequency = 0;
        for(int j = 0; j < asciiStrLength; j++)
        {
            if(tolower(encodedAsciiStr[j]) == alphabet[i]) charFrequency++;
        }
    }
}

double computeFittingQuotient(const char *encodedStr, const unsigned char key)
{
    //use the calculated character frequencies to compute fitting quotient
    //TODO: Add logic

    return 0;
}
