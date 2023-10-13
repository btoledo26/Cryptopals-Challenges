#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

#include "Single-byte_XOR.h"

void test1();
void test2();
void test3();
void test4();
void test5();

int main()
{
    test1();
    //test2();
    //test3();
    //test4();
    test5();

    return 0;
}

void test1()
{
    char encryptedString[] = "5435667D7A67613566707B61707B7670";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    uint8_t key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    assert(key == 21);
    cout << "Passed Test 1\n" << endl;
}

void test2()
{
    char encryptedString[] = "";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    uint8_t key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    //assert(key == 55);
    cout << "Passed Test 2\n" << endl;
}

void test3()
{
    char encryptedString[] = "";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    uint8_t key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    //assert(key == 67);
    cout << "Passed Test 3\n" << endl;
}

void test4()
{
    char encryptedString[] = "";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    uint8_t key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    //assert(key == 30);
    cout << "Passed Test 4\n" << endl;
}

void test5()
{
    char encryptedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int encryptedStrLength = sizeof(encryptedString) / sizeof(char);

    uint8_t key = findSingleByteXORCipherKey(encryptedString, encryptedStrLength);
    decryptSingleByteXOR(encryptedString, encryptedStrLength, key);

    assert(key == 88);
    cout << "Passed Test 5" << endl;
}
