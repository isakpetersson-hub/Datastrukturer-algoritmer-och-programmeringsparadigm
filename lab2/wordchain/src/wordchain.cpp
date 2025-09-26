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

list<string> findNeighbor(string word){
    //do shit
}

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
            cout << "Chain found" << endl;
            break;
        }
        else{
            list<string> neighbor = findNeighbor(current.top());
            for(string neighbor : neighbor){
                if(usedWords.count(neighbor) == 1){ // Weird ass lösning finns nog bättre
                    usedWords.insert(neighbor);
                    stack<string> copycurrent = current;
                    copycurrent.push(neighbor);
                    wordQueue.push(copycurrent);
                }
            }
        }
    return 0;
    }
}
