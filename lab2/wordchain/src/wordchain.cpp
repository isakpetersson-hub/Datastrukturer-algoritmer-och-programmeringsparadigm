// isape817 rasda103

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <unordered_set>

using namespace std;

const char ALPHABET[]  = "abcdefghijklmnopqrstuvwxyz";

void findNeighbours(const string& word, const unordered_set<string>& dictionary, list<string>& neighbours);
void printWordChain( stack<string>& chain );

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

    queue<stack<string>> wordQueue;
    unordered_set<string> usedWords; //Weird ass lösning finns nog bättre

    stack<string> current;
    current.push(start);
    wordQueue.push(current);

    while( !wordQueue.empty()){
        current = wordQueue.front();
        wordQueue.pop();
        if(current.top() == end){
            printWordChain( current );
            break;
        }
        else{
            list<string> neighbours;
            findNeighbours( current.top(), dict, neighbours );
            for(auto neighbour : neighbours){
                if(usedWords.count(neighbour) == 0){ // Weird ass lösning finns nog bättre
                    usedWords.insert(neighbour);
                    stack<string> copycurrent = current;
                    copycurrent.push(neighbour);
                    wordQueue.push(copycurrent);
                }
            }
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}

void findNeighbours(const string& word, const unordered_set<string>& dictionary, list<string>& neighbours){
    // Uses the global constant ALPHABET and a dictionary of valid words to find "neighbour-words" for the given word

    for( unsigned int i = 0; i < word.length(); i++ ) {
        string tempWord = word;
        for( unsigned int j = 0; j < 26; j++ ) {
            tempWord.replace(i, 1, string(1, ALPHABET[j]));
            if( dictionary.count(tempWord) == 1) {
                neighbours.push_back(tempWord);
            }
        }
    }
}

void printWordChain( stack<string>& chain ) {
    // Simply prints out a chain of words
    while (!chain.empty()) {
        cout << chain.top() << " ";
        chain.pop();
    }
    cout << endl;
}
