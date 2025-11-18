// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include <grid.h>
#include "lexicon.h"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them
    void setUpGame();
    void startGame();

private:
    // TODO: decide the private member variables/functions and declare them
    int playerScore, computerScore, playerWordAmount, computerWordAmount;
    vector<string> playerWords, computerWords;
    Grid<char> board;
    Lexicon lexicon;

    void printBoard();
    void shuffleBoard();
    void inputBoard();
    bool isAlphabetical(const string& input);
    bool isValidWord(const string& word);
    bool hasBeenGuessed(const string& word, const vector<string>& guessedWords);
    bool containsWord(const string& word, const int size, int index, int r, int c);
};

#endif
