// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// TODO: implement the members you declared in Boggle.h

void Boggle::setUpGame() {
    playerScore = computerScore = playerWordAmount = computerWordAmount = 0;
    playerWords.clear();
    computerWords.clear();
    board.resize(BOARD_SIZE, BOARD_SIZE);
    lexicon = Lexicon("EnglishWords.dat");

    std::cout << "Do you want to generate a random board? " << std::ends;
    while ( true ) {
        string answer;
        getline(cin, answer);
        answer = trim(toLowerCase(answer));

        if (startsWith(answer, 'y')) {
            shuffleBoard();
            break;
        }
        if (startsWith(answer, 'n')) {
            inputBoard();
            break;
        }
        std::cout << "'" << answer << "' is not a valid response!" << endl;
    }
}

void Boggle::startGame() {	// Assumes the board already exists
    cout << "It's your turn!" << endl;
    printBoard();

    string wordList = "";
    while( true ) {
        printf("\nYour words (%d): %s", playerWordAmount, wordList.c_str());
        printf("\nYour score: %d", playerScore);
        printf("\nType a word (or press Enter\n\tto end your turn): ");
        string input;
        cin >> input;
        input = toUpperCase(input);
        if (!isValidWord(input)) {
            printf("\nNot a valid word!");
            continue;
        } else {
            playerWords.push_back(input);
        }
    }
}

bool Boggle::isValidWord(const string& word) {
    if (word.size() < 4) {
        cout << "Word is too short" << endl;
        return false;
    } else if (hasBeenGuessed(word, playerWords)) {
        return false;
    } else if (!lexicon.contains(word)) {
        cout << "Word does not exist in lexicon" << endl;
        return false;
    }

    return containsWord( word, word.size(), 0, 0, 0);
}

bool Boggle::containsWord(const string& word, const int size, int index, int r=0, int c=0) {
    if (index == size) {
        cout << "Walla index == size" << endl;
        return true;
    }

    char soughtChar = word[index];
    if (index == 0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board.get(i, j) == soughtChar) {
                    cout << "First char found" << endl;
                    if (containsWord( word, size, index + 1, i, j )) {
                        return true;
                    }
                }
            }
        }
        return false;
    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (board.inBounds(r+i, c+j) && (board.get(r+i, c+j) == soughtChar) && !((i == 0) && (j == 0))) {
                    printf("Char at index %d found", index);
                    if (containsWord( word, size, index + 1, r + i, c + j )) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

bool Boggle::hasBeenGuessed(const string& word, const vector<string>& guessedWords) {
    for (auto guessed : guessedWords) {
        if (word == guessed) {
            return true;
        }
    }
    return false;
}

void Boggle::printBoard() {
    string output;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            output.append( string { board.get(i, j) } );
        }
        output.append("\n");
    }
    cout << output << ends;
}

void Boggle::shuffleBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.set(i, j, CUBES[i + j][randomInteger(0, CUBE_SIDES - 1)]);
        }
    }

    shuffle(board);
}

void Boggle::inputBoard() {
    cout << "Please enter a manual board layout: " << ends;

    string input;
    while( true ) {
        cin >> input;
        if (input.size() != 16) {
            printf("Input must be 16 letters (Input was %d letters): ", (int) input.size());
        } else if (!isAlphabetical(input)) {
            printf("Input most only contain alphabetical characters: ");
        } else {
            break;
        }
    }

    input = toUpperCase(input);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.set(i, j, input[4*i + j]);
        }
    }
}

bool Boggle::isAlphabetical(const string &input) {
    for ( const auto ch : input ) {
        if (!std::isalpha(static_cast<unsigned char>(ch)))
            return false;
    }
    return true;
}
