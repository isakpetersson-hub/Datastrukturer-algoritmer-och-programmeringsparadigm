#include <iostream>
#include<iostream>
#include<fstream>
#include<unordered_set>
#include<list>
#include<map>

using namespace std;

void readDictionary( unsigned int wordSize, unordered_set<string>& dict );
void setupHangman( list<char>& guessedLetters, unordered_set<string>& dict, unsigned int& wordSize, unsigned int& guessCount, bool& showWordList, string& currentWord, bool& wordGuessed );

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

int main() {
    cout << "Welcome to Hangman." << endl;

    list<char> guessedLetters;
    unordered_set<string> dict;

    unsigned int wordSize;
    unsigned int guessCount;

    bool showWordList;

    string currentWord;
    bool wordGuessed;
    char guess;

    setupHangman( guessedLetters, dict, wordSize, guessCount, showWordList, currentWord, wordGuessed );

    while(!wordGuessed){
        cout << "You have " << guessCount << " guesses left" << endl;
        cout << "You have guessed the letters ";
        for( auto letter : guessedLetters ) {
            cout << letter;
        }
        cout << endl;

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
        unsigned int largetSetSize = 0;
        string largetSetKey = "";
        for ( auto familyPair: familyMap){
            if (familyPair.second.size() > largetSetSize){
                largetSetKey = familyPair.first;
                largetSetSize = familyPair.second.size();
            }
        }
        dict = familyMap.at(largetSetKey);
        for(unsigned int i = 0; i < largetSetKey.size(); i++){
            if (largetSetKey[i] == '1'){
                currentWord.replace(i,1, {guess});
            }
        }
        if (largetSetKey.find( '1') == string::npos)
            cout << "You guessed wrong" << endl;
        else
            cout << "You guessed correct" << endl;

        for ( auto letter: currentWord){
            wordGuessed = true;
            if (letter == '_') {
                wordGuessed = false;
                break;
            }
        }
        cout << currentWord << endl;

        if (wordGuessed) {
            cout << "Congrats! You have defeated the Evil Hangman! Would you like to play again? (y/n)" << endl;
            string answer;
            cin >> answer;
            if (answer == "y") {
                setupHangman(guessedLetters, dict, wordSize, guessCount, showWordList, currentWord, wordGuessed);
            } else {
                cout << "Thanks for playing!" << endl;
            }
        }
        if(guessCount == 0){
            cout << "You failed to defeat the Evil Hangman! The correct word is " << *dict.begin() << endl;
            cout << "Would you like to play again? (y/n)" << endl;
            string answer;
            cin >> answer;
            if (answer == "y") {
                setupHangman(guessedLetters, dict, wordSize, guessCount, showWordList, currentWord, wordGuessed);
            } else {
                cout << "Thanks for playing!" << endl;
            }
        }
    }
    return 0;
}


void setupHangman( list<char>& guessedLetters, unordered_set<string>& dict, unsigned int& wordSize, unsigned int& guessCount, bool& showWordList, string& currentWord, bool& wordGuessed ) {
    guessedLetters.clear();

    wordSize = 0;
    dict.clear();
    while( dict.size() < 1 ) {
        cout << "Enter wordsize: " << ends;
        cin >> wordSize;
        readDictionary( wordSize, dict );
    }

    guessCount = 0;
    while( guessCount < 1) {
        cout << "Enter guessCount: " << ends;
        cin >> guessCount;
    }

    cout << "Do you want to see the wordcount: 1 to show, 0 to not show: " << ends;
    cin >> showWordList;

    currentWord.clear();
    for( unsigned int i = 0; i < wordSize; i++ ) {
        currentWord.append("_");
    }
    cout << currentWord << endl;

    wordGuessed = false;
}


void readDictionary( unsigned int wordSize, unordered_set<string>& dict ) {
    string word;
    ifstream fileStream("dictionary.txt");
    while( getline( fileStream, word ) ) {
        if (word.length() == wordSize)
            dict.insert(word);
    }
}
