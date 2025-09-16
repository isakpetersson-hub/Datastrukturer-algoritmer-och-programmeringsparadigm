#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
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
    // TODO: Finish the program!

    ifstream dictionary("dictionary.txt");
    string word;
    set<string> dict;

    while( getline(dictionary, word)) {
        dictionary >> word;
        dict.insert(word);
    }



    return 0;
}
