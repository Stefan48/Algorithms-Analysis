#include "algo.h"
#include <iostream>
#include <cstring>
#include <vector>

#define MAX_LENGTH 100000

using namespace std;

int main(void)
{
    // read input from stdin
    int length;
    
    char *text = new char[MAX_LENGTH];
    cin.getline(text, MAX_LENGTH);
    length = strlen(text) - 1;
    text[length] = '\0';
    text = (char*) realloc(text, length * sizeof(char));
    
    char *pattern = new char[MAX_LENGTH];
    cin.getline(pattern, MAX_LENGTH);
    length = strlen(pattern) - 1;
    pattern[length] = '\0';
    pattern = (char*) realloc(pattern, length * sizeof(char));
    
    // call search function and output result to stdout
    std::vector<int> indexes = search(text, pattern);
    if(indexes.size())
        for (auto it = indexes.cbegin(); it != indexes.cend(); ++it)
		    cout << *it << " ";
    else cout << "not found";
	cout << "\n";
    
    return 0;
}
