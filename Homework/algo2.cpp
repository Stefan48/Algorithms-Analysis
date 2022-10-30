// Boyer-Moore algorithm

#include "algo.h"
#include <cstring>

#define ALPHABET_LENGTH 256

// bad character preprocessing
void badCharacterPreprocess(const char *pattern, int pattern_length, int bad_character_array[])
{
    int i;
    for(i = 0; i < ALPHABET_LENGTH; ++i)
        bad_character_array[i] = -1;
    for(i = 0; i < pattern_length; ++i)
        bad_character_array[(int)pattern[i]] = i; // last occurence of each character
}

// good suffix case 1 preprocessing
void goodSuffixPreprocess1(const char *pattern, int pattern_length, int border_position[], int shift[])
{
    int i = pattern_length, j = pattern_length + 1;
    border_position[i] = j;
    while (i > 0)
    {
        // if character at i - 1 doesn't match character at j - 1
        // then continue searching to the right of the pattern for border
        while (j <= pattern_length && pattern[i - 1] != pattern[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = border_position[j];
        }
        // pattern[i - 1] matched with pattern[j - 1], border found
        i--;
        j--;
        border_position[i] = j;
    }
}

// good suffix case 2 preprocessing
void goodSuffixPreprocess2(int pattern_length, int border_position[], int shift[])
{
    int i, j = border_position[0];
    for (i = 0; i <= pattern_length; ++i)
    {
        // set the border position of the first character of the pattern to all indexes equal to 0
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = border_position[j];
    }
}

// preprocessing
void preprocess(const char *pattern, int pattern_length, int bad_character_array[], int border_position[], int shift[])
{
    badCharacterPreprocess(pattern, pattern_length, bad_character_array);
    goodSuffixPreprocess1(pattern, pattern_length, border_position, shift);
    goodSuffixPreprocess2(pattern_length, border_position, shift);
}

// search
std::vector<int> search(const char *text, const char *pattern)
{
    std::vector<int> indexes; // the return vector, will contain all match indexes
    int i = 0, j;
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);
    int bad_character_array[ALPHABET_LENGTH];
    int border_position[pattern_length + 1];
    for(i = 0; i <= pattern_length; ++i)
        border_position[i] = 0;
    int shift[pattern_length + 1];
    for(i = 0; i <= pattern_length; ++i)
        shift[i] = 0;
        
    preprocess(pattern, pattern_length, bad_character_array, border_position, shift);
    
    i = 0;
    while (i <= text_length - pattern_length)
    {
        j = pattern_length - 1;
        while (j >= 0 && pattern[j] == text[i + j])
            j--;
        if (j < 0)
        {
            // it's a match
            indexes.push_back(i);
            i += shift[0];
        }
        else
        {
            // use the maximum shift of bad character and good suffix heuristics
            i += std::max(shift[j + 1], j - bad_character_array[(int)text[i + j]]);
        }
    }
    return indexes;
}
