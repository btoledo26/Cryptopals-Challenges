///////////////////////////////////////////////////////////////////////////////
// Cryptopals Challenges
// Set 1: Basics
// Challenge 1 - Hex to Base64
// 2/13/2023
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cout;
using std::endl;

#define HEX_CHUNK_SIZE 6
#define BINARY_CHUNK_SIZE 24

static const char *const BASE_64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //constant pointer to constant char, neither to be modified

size_t getResultLength(size_t hexBytes);
void hexToBase64(char *hexVals, char *base64Vals, int hexLength);
void hexChunkToBinaryChunk(char *hexChunk, char *binaryChunk, int hexChunkSize);
void binaryToBase64(char* binaryChunk, char *base64Vals, size_t *index);

int main()
{
    char hexChars[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    size_t hexLength = sizeof(hexChars) / sizeof(char) - 1;
    if(hexLength % 2 != 0)
    {
        cout << "Hex input length must be divisible by 2" << endl;
        return -1;
    }

    size_t base64Length = getResultLength(hexLength) + 1;
    char *base64Chars = (char*)malloc(base64Length);
    if(base64Chars != nullptr)
    {
        memset(base64Chars, 0, base64Length);
        hexToBase64(hexChars, base64Chars, hexLength);

        cout << "Hex: " << hexChars << endl;
        cout << "Base64: " << base64Chars << endl;

        free(base64Chars);
    }

    return 0;
}

/******************************************************************************
* Calculates length of resulting base64 array using length of hex array. Rounds
* to the nearest 4 for padding.
*
* hexBytes - the size of the array containing the original hex string
*
* Returns the calculated length the base64 result array.
* 
******************************************************************************/
size_t getResultLength(size_t hexBytes)
{
    size_t size = (hexBytes * 4 + 2) / 3;
    size /= 2;
    size_t remainder = size % 4;
    if (remainder != 0) size += (4 - remainder);

    return size;
}

/******************************************************************************
* Converts hex string to base64 string by converting hex chunks into binary 
* and storing in a 24-byte array, grouping the array into groups of 6 bytes, 
* and using these sextets' decimal values to look up the corresponding base64 
* value in the character string defined above.
* 
* hexVals - char array containing the original hex string
* base64Vals - the char array to store converted base64 values in
* size - the size of the array containing the original hex string
* 
******************************************************************************/
void hexToBase64(char *hexVals, char *base64Vals, int hexLength)
{
    char hexChunk[HEX_CHUNK_SIZE + 1] = "";
    char binaryChunk[BINARY_CHUNK_SIZE + 1] = "";
    int remainingChars = hexLength;
    size_t encodeIndex = 0;
    for(int i = 0; i < hexLength; i += HEX_CHUNK_SIZE, remainingChars -= HEX_CHUNK_SIZE)
    {
        memset(hexChunk, 0, HEX_CHUNK_SIZE + 1);
        memset(binaryChunk, 0, BINARY_CHUNK_SIZE + 1);

        if (remainingChars < 6) //last chunk is a partial chunk
        {
            int remainder = remainingChars % 6;
            memcpy(hexChunk, hexVals + i, remainder);
            hexChunkToBinaryChunk(hexChunk, binaryChunk, remainder);
        }
        else
        {
            memcpy(hexChunk, hexVals + i, HEX_CHUNK_SIZE);
            hexChunkToBinaryChunk(hexChunk, binaryChunk, HEX_CHUNK_SIZE);
        }

        binaryToBase64(binaryChunk, base64Vals, &encodeIndex);
    }
}

/******************************************************************************
* Converts HEX_CHUNK_SIZE hex characters at a time from hexChunk to binary and 
* stores them in binaryChunk.
*
* hexChunk - char array containing HEX_CHUNK_SIZE characters from the hex string
* binaryChunk - char array where binary representation of the hexChunk are stored
* hexChunkSize - length of passed in hexChunk
*
******************************************************************************/
void hexChunkToBinaryChunk(char *hexChunk, char *binaryChunk, int hexChunkSize)
{
    for (int i = 0, j = 0; i < hexChunkSize; i++, j+=4)
    {
        switch (toupper(hexChunk[i]))
        {
            case '0': memcpy(binaryChunk + j, "0000", 4); continue;
            case '1': memcpy(binaryChunk + j, "0001", 4); continue;
            case '2': memcpy(binaryChunk + j, "0010", 4); continue;
            case '3': memcpy(binaryChunk + j, "0011", 4); continue;
            case '4': memcpy(binaryChunk + j, "0100", 4); continue;
            case '5': memcpy(binaryChunk + j, "0101", 4); continue;
            case '6': memcpy(binaryChunk + j, "0110", 4); continue;
            case '7': memcpy(binaryChunk + j, "0111", 4); continue;
            case '8': memcpy(binaryChunk + j, "1000", 4); continue;
            case '9': memcpy(binaryChunk + j, "1001", 4); continue;
            case 'A': memcpy(binaryChunk + j, "1010", 4); continue;
            case 'B': memcpy(binaryChunk + j, "1011", 4); continue;
            case 'C': memcpy(binaryChunk + j, "1100", 4); continue;
            case 'D': memcpy(binaryChunk + j, "1101", 4); continue;
            case 'E': memcpy(binaryChunk + j, "1110", 4); continue;
            case 'F': memcpy(binaryChunk + j, "1111", 4); continue;
        }
    }
}

/******************************************************************************
* Converts the array of binary values stored in binaryChunk into their decimal
* value, uses this value to lookup the base64 character, and stores this character.
*
* binaryChunk - the char array containing binary values to be converted to decimal
* base64Vals - the char array to store converted base64 values in
* index - pointer to the index of base64Vals
*
******************************************************************************/
void binaryToBase64(char *binaryChunk, char *base64Vals, size_t *index)
{
    int characters = strnlen(binaryChunk, BINARY_CHUNK_SIZE);
    for (int i = 0; i < characters; i + 6)
    {
        size_t total = 0;
        for (int j = 5; j > -1; j--, i++)
        {
            if(binaryChunk[i] == '1')
                total += (1 * pow(2, j));
        }
        
        base64Vals[(*index)++] = BASE_64_ALPHABET[total];
    }

    if (BINARY_CHUNK_SIZE - characters > 0) //add padding chars if needed
    {
        for(int i = 0; i < (BINARY_CHUNK_SIZE - characters) / 6; i++)
            base64Vals[(*index)++] = '=';
    }
}