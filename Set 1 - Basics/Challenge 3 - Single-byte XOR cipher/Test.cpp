#include <iostream>
using std::cout;
using std::endl;

#include "Single-byte_XOR.h"

int main()
{
    char encryptedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    char key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    return 0;
}