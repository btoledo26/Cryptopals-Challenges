///////////////////////////////////////////////////////////////////////////////
// Cryptopals Challenges
// Set 1: Basics
// Challenge 2 - Fixed XOR
// 9/11/2023
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <cassert>

char HexToNumVal(char c);
string StrFixedXOR(string bufferA, string bufferB);

int main()
{
    string bufferA("1c0111001f010100061a024b53535009181c");
    string bufferB("686974207468652062756c6c277320657965");

    string result = StrFixedXOR(bufferA, bufferB);
    assert(result == "746865206b696420646f6e277420706c6179");

    cout << "Input A: " << bufferA << "\nInput B: " << bufferB << "\nXOR Result: " << result << endl;

    return 0;
}

/******************************************************************************
* Converts the hex value char to its integer value.
*
* c - the character to be converted to integer equivalent
*
* Returns: the integer equivalent of the char passed in.
* 
******************************************************************************/
char HexToNumVal(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (tolower(c) >= 'a' && tolower(c) <= 'f') return (c - 'a') + 10;
    return -1;
}

/******************************************************************************
* Produces the XOR result of two input buffers of equal length.
*
* bufferA - the first buffer of hex values
* bufferB - the second buffer of hex values
* 
* Returns: the XOR result of the two buffers.
* 
******************************************************************************/
string StrFixedXOR(string bufferA, string bufferB)
{
    assert(bufferA.length() == bufferB.length());

    char hexAlphabet[] = "0123456789abcdef";
    string resultString;
    for (int i = 0; i < bufferA.length(); i++)
    {
        unsigned char resultChar = HexToNumVal(bufferA[i]) ^ HexToNumVal(bufferB[i]);
        resultString.push_back(hexAlphabet[resultChar]);
    }

    return resultString;
}
