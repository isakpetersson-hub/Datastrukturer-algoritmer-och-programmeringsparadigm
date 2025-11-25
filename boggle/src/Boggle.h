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

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    void setUpGame();
    void startGame();

private:
    int playerScore, computerScore, playerWordAmount, computerWordAmount;
    vector<string> playerWords, computerWords;
    Grid<tuple<char, bool>> board;
    Lexicon lexicon;

    void printBoard();
    void shuffleBoard();
    void inputBoard();
    bool isAlphabetical(const string& input);
    bool isValidWord(const string& word);
    void findAllWords(vector<string>& target);
    bool hasBeenGuessed(const string& word, const vector<string>& guessedWords);
    bool containsWord(const string& word, const int size, int index, int r, int c);
    void checkNeighbours(vector<string>& target, string current, int r, int c);
    vector<tuple<int,int>> findNeighbours(int r, int c);
    string wordsToString(const vector<string>& words);
};

#endif
