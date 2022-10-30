// Rabin-Karp algorithm

#include "algo.h"
#include <cstring>

#define ALPHABET_LENGTH 256
#define PRIME_NUMBER 31

std::vector<int> search(const char *text, const char *pattern)
{
    std::vector<int> indexes; // the return vector, will contain all match indexes
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);
    int text_hash = 0;
    int pattern_hash = 0;
    int power = 1; // pow(ALPHABET_LENGTH, pattern_length - 1) % PRIME_NUMBER
    for(int i = 0; i < pattern_length - 1; ++i)
        power = (power * ALPHABET_LENGTH) % PRIME_NUMBER;
        
    // calculate hash value for the pattern and the first window of text
    for(int i = 0; i < pattern_length; ++i)
    {
        text_hash = (ALPHABET_LENGTH * text_hash + text[i]) % PRIME_NUMBER;
        pattern_hash = (ALPHABET_LENGTH * pattern_hash + pattern[i]) % PRIME_NUMBER;
    }
    // slide the pattern over the text one by one
    for(int i = 0; i <= text_length - pattern_length; ++i)
    {
        // check if hash values match
        if(pattern_hash == text_hash)
        {
            // check the characters one by one
            int j;
            for(j = 0; j < pattern_length; ++j)
                if(text[i + j] != pattern[j])
                    break;
            if(j == pattern_length)
            {
                // it's a match
                indexes.push_back(i);
            }
        }
        // calculate hash value for the next window of text
        // (remove most significant digit, add least significant digit)
        if(i < text_length - pattern_length)
        {
            text_hash = (ALPHABET_LENGTH * (text_hash - text[i] * power) + text[i + pattern_length]) % PRIME_NUMBER;
            // make sure hash value is positive
            if(text_hash < 0)
                text_hash += PRIME_NUMBER;
        }
    }
    return indexes;
}