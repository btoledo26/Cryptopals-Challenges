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
#include <vector>
using std::vector;

#define ALPHABET_LENGTH 26
#define POSSIBLE_KEYS 256

//https://mathcenter.oxford.emory.edu/site/math125/englishLetterFreqs/
static const map<char, double> charFrequency = { {'e', 12.702}, {'t', 9.056}, {'a', 8.167}, {'o', 7.507}, {'i', 6.966}, {'n', 6.749},
                                                 {'s', 6.327}, {'h', 6.094}, {'r', 5.987}, {'d', 4.253}, {'l', 4.025}, {'c', 2.782},
                                                 {'u', 2.758}, {'m', 2.406}, {'w', 2.360}, {'f', 2.228}, {'g', 2.015}, {'y', 1.974},
                                                 {'p', 1.929}, {'b', 1.492}, {'v', 0.978}, {'k', 0.772}, {'j', 0.153}, {'x', 0.150},
                                                 {'q', 0.095}, {'z', 0.074} };
static map<char, double> textCharFrequency = {};
static map<char, double> keyScores = {};
static const char *const alphabet = "abcdefghijklmnopqrstuvwxyz";

uint8_t findCipherKey(const char *encodedString, const int encodedStrLength);
char HexToIntVal(const char c);
void convertHexToASCII(const char *hexString, const int hexStrLength, vector<uint8_t> *encodedAsciiChars);
void decode(vector<uint8_t> &encodedAsciiChars, vector<uint8_t> &decodedAsciiChars, const uint8_t key);
void calculateCharacterFrequencies(vector<uint8_t> &decodedAsciiChars);
double computeFittingQuotient(vector<uint8_t> &decodedAsciiChars, const uint8_t key);

int main()
{
    char encodedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int encodedStrLength = sizeof(encodedString) / sizeof(char) - 1;

    char key = findCipherKey(encodedString, encodedStrLength);

    //TODO: remove need to pass in pointer for decoded string and just decode the string using the returned key after it is found

    //cout << "Encoded String: " << encodedString << "\nDecoded String: " << decodedString << "\nKey: " << key << endl;

    return 0;
}

/******************************************************************************
* Finds the byte key to decode the cipher text with.
*
* encodedString - the encoded cipher text
* encodedStrLength - the length of the cipher string once converted from hex to 
*                       ASCII
*
* Returns: the single-byte cipher key used to decode the cipher text.
*
******************************************************************************/
uint8_t findCipherKey(const char *encodedString, const int encodedStrLength)
{
    char key = -1;
    vector<uint8_t> encodedAsciiChars;
    vector<uint8_t> decodedAsciiChars;

    convertHexToASCII(encodedString, encodedStrLength, &encodedAsciiChars);

    for(int i = 0; i < POSSIBLE_KEYS; i++) //try each possible key and calculate scores
    {
        if(!decodedAsciiChars.empty()) decodedAsciiChars.clear();
        decode(encodedAsciiChars, decodedAsciiChars, i);

        //Debug print
        /*cout << "Key: " << i << " ";
        for(int i = 0; i < decodedAsciiChars.size(); i++)
        {
            cout << decodedAsciiChars[i];
        }
        cout << endl;*/

        //double keyScore = computeFittingQuotient(decodedAsciiChars, i);
        //keyScores.insert(std::pair<char, double>(alphabet[i], keyScore));
    }

    //find best scoring key in map and store in key variable

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
* encodedAsciiChars - the encoded cipher text in ASCII form
*
******************************************************************************/
void convertHexToASCII(const char *hexString, const int hexStrLength, vector<uint8_t> *encodedAsciiChars)
{
    for(int i = 0, j = 0; i < hexStrLength; i++, j++)
    {
        uint8_t c = HexToIntVal(hexString[i]);
        encodedAsciiChars->push_back((c << 4) + HexToIntVal(hexString[++i]));
    }
}

/******************************************************************************
* XORs each character of the encoded string with a single byte key.
*
* encodedAsciiChars - vector containing the encoded string in ASCII form
* decodedAsciiChars - vector where the decoded string is to be stored
* key - the byte key used to decode the string
*
******************************************************************************/
void decode(vector<uint8_t> &encodedAsciiChars, vector<uint8_t> &decodedAsciiChars, const uint8_t key)
{
    for(int i = 0; i < encodedAsciiChars.size(); i++)
    {
        decodedAsciiChars.push_back(encodedAsciiChars[i] ^ key);
    }
}

/******************************************************************************
* Calculates the character frequency of each alphabet character in the cipher
* text.
* 
* decodedAsciiChars - vector containing the decoded ASCII characters
* 
******************************************************************************/
void calculateCharacterFrequencies(vector<uint8_t> &decodedAsciiChars)
{
    //calculate the frequency of each letter in the alphabet in the encoded string and store in struct array
    //TODO: Add logic

    for(int i = 0; i < ALPHABET_LENGTH; i++)
    {
        double charFrequency = 0;
        for(int j = 0; j < decodedAsciiChars.size(); j++)
        {
            if(tolower(decodedAsciiChars[j]) == alphabet[i]) charFrequency++;
        }
    }
}

double computeFittingQuotient(vector<uint8_t> &decodedAsciiChars, const uint8_t key)
{
    //use the calculated character frequencies to compute fitting quotient
    //TODO: Add logic

    return 0;
}
