// isape817 rasda103

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const char ALPHABET[]  = "abcdefghijklmnopqrstuvwxyz";

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string start, end;
    cin >> start;
    cin >> end;
    cout << "Chain from " << end << " back to " << start << endl;

    ifstream fileStream("dictionary.txt");
    string word;
    unordered_set<string> dict;

    while( getline(fileStream, word)) {
        fileStream >> word;
        dict.insert(word);
    }

    if ( dict.count("hello") == 1)
        cout << "found" << endl;

    return 0;
}
