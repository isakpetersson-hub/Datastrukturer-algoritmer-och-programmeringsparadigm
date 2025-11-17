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
    std::cout << "It's your turn!" << std::endl;
    printBoard();

    printf("\nYour words (%d): ", playerWordAmount);
}

void Boggle::printBoard() {

}

void Boggle::shuffleBoard() {

}

void Boggle::inputBoard() {

}
