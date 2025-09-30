#include <iostream>
#include<iostream>
#include<fstream>
#include<unordered_set>
#include<list>
#include<map>

using namespace std;

void readDictionary( unsigned int wordSize, unordered_set<string>& dict );

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

int main() {
    cout << "Welcome to Hangman." << endl;

    list<char> guessedLetters;
    unordered_set<string> dict;
    unsigned int wordSize = 0;
    while( dict.size() < 1 ) {
        cout << "Enter wordsize: " << ends;
        cin >> wordSize;
        readDictionary( wordSize, dict );
    }

    unsigned int guessCount = 0;
    while( guessCount < 1) {
        cout << "Enter guessCount: " << ends;
        cin >> guessCount;
    }

    bool showWordList;
    cout << "Do you want to see the wordcount: 1 to show, 0 to not show: " << ends;
    cin >> showWordList;

    string currentWord;
    for( unsigned int i = 0; i < wordSize; i++ ) {
        currentWord.append("_");
    }
    char guess;
    while(true){
        cout << "You have " << guessCount << " guesses left" << endl;
        cout << "You have guessed the letters ";
        for( auto letter : guessedLetters ) {
            cout << letter + " ";
        }
        cout << endl;

        cout << currentWord << endl;

        if( showWordList)
            cout << "There are " << dict.size() << " words left" << endl;

        cout << "What is your next guess?" << endl;
        bool validguess = false;
        while (!validguess){
            validguess = true;
            cin >> guess;
            for ( auto letter : ALPHABET){
                if (guess == letter){
                    for ( auto letter2 : guessedLetters){
                        if (guess == letter2){
                            validguess = false;
                            break;
                        }

                    }
                }

            }
        }
        guessCount--;
        guessedLetters.push_back(guess);
        map<string,unordered_set<string>> familyMap;
        for ( auto word: dict){
            string wordFamily = "";
            for ( auto letter: word){
                if ( letter == guess)
                    wordFamily.append("1");
                else
                    wordFamily.append("0");
            }
            if( familyMap.count(wordFamily) > 0)
                familyMap.at(wordFamily).insert(word);
            else{
                unordered_set<string> familySet = {word};
                familyMap[wordFamily] = familySet;
            }
        }
        //Hitta största set
    }
    return 0;
}


void readDictionary( unsigned int wordSize, unordered_set<string>& dict ) {
    string word;
    ifstream fileStream("di.txt");

    while( getline( fileStream, word ) ) {
        cout << word << endl;
        if (word.length() == wordSize)
            dict.insert(word);
    }
}
