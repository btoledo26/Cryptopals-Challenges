#pragma once

#include <vector>
using std::vector;
#include <map>
using std::map;

#define ALPHABET_LENGTH 26
#define POSSIBLE_KEYS 256

uint8_t findSingleByteXORCipherKey(const char *encodedString, const int encodedStrLength);
void decryptSingleByteXOR(vector<uint8_t> &encodedAsciiChars, vector<uint8_t> &decodedAsciiChars, const uint8_t key);
void decryptSingleByteXOR(const char *encodedString, const int encodedStrLength, uint8_t key);
char hexToIntVal(const char c);
void convertHexToASCII(const char *hexString, const int hexStrLength, vector<uint8_t> *encodedAsciiChars);
double calculateFittingQuotient(vector<uint8_t> &decodedAsciiChars);
uint8_t getMaxValueKey(map<uint8_t, double> &valueMap);
void printDecryptionResult(vector<uint8_t> &decodedAsciiChars, uint8_t key);