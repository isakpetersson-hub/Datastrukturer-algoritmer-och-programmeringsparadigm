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

    while( true ) {
        printBoard();
        printf("\nYour score: %d", playerScore);
        printf("\nType a word (or press Enter\n\tto end your turn): ");
        string input = "";
        getline(cin, input);
        if (input.size() == 0) {
            break;
        }
        input = toUpperCase(input);
        if (!isValidWord(input)) {
            printf("\nNot a valid word!");
            continue;
        } else {
            playerWords.push_back(input);
            playerScore += input.size() - 3;
        }
    }
    findAllWords(computerWords);
    printf("\nMy words (%zu): %s", computerWords.size(), wordsToString(playerWords).c_str());
}

vector<tuple<int,int>> Boggle::findNeighbours(int r, int c){
    vector<tuple<int,int>> Neighbours;
    for (int i = -1 ; i <= 1; i++){
        for ( int j = -1 ; j <= 1; j++){
            if (board.inBounds(r+i, c+j) && !((i == 0) && (j == 0)) && get<1>(board.get(r+i,c+j)) == false) {
                Neighbours.push_back({r+i, c+j});
            }
        }
    }
    return Neighbours;
}

void Boggle::checkNeighbours(vector<string>& target, string current, int r, int c){
    //if ( lexicon.contains(current) && target.)
    char letter = get<0>(board.get(r,c));
    board.set(r,c,{letter,true});
    for ( auto n : findNeighbours(r,c)){
        if ( lexicon.containsPrefix(current + get<0>(board.get(get<0>(n),get<1>(n)))) == false){
           continue;
         }
         current.append(string{get<0>(board.get(get<0>(n),get<1>(n)))});
         checkNeighbours(target, current, r, c);
    }
    board.set(r,c,{letter,false});
}

void Boggle::findAllWords(vector<string>& target) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            checkNeighbours(target, string{get<0>(board.get(i,j))}, i, j);
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
        return true;
    }

    char soughtChar = word[index];
    if (index == 0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (get<0>(board.get(i, j)) == soughtChar) {
                    if (containsWord( word, size, index + 1, i, j )) {
                        return true;
                    }
                }
            }
        }
        cout << "Word: " << word << ", Index: " << index << endl;
        return false;
    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (board.inBounds(r+i, c+j) && (get<0>(board.get(r+i, c+j)) == soughtChar) && !((i == 0) && (j == 0))) {
                    if (containsWord( word, size, index + 1, r + i, c + j )) {
                        return true;
                    }
                }
            }
        }
        cout << "Word: " << word << ", Index: " << index << endl;
        return false;
    }
}

string Boggle::wordsToString(const vector<string>& words) {
    string output = "{";
    for (auto& word : words) {
        output.append("\"" + word + "\"");
        if (word != words.back()) {
            output.append(", ");
        }
    }
    output.append("}");
    return output;
}

bool Boggle::hasBeenGuessed(const string& word, const vector<string>& guessedWords) {
    for (auto& guessed : guessedWords) {
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
            output.append( string { get<0>(board.get(i, j)) } );
        }
        output.append("\n");
    }
    cout << output << ends;
}

void Boggle::shuffleBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.set(i, j, make_tuple(CUBES[i + j][randomInteger(0, CUBE_SIDES - 1)], false));
        }
    }

    shuffle(board);
}

void Boggle::inputBoard() {
    cout << "Please enter a manual board layout: " << ends;

    string input;
    while( true ) {
        getline(cin, input);
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
            board.set(i, j, make_tuple(input[4*i + j], false));
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
