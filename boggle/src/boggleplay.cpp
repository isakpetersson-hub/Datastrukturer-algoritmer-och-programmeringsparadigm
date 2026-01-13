// isape817 rasda103

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    std::cout << "Do you want to generate a random board? (Y/N): " << std::ends;
    while ( true ) {
        string answer;
        getline(cin, answer);
        answer = trim(toLowerCase(answer));

        if (startsWith(answer, 'y')) {
            boggle.setUpGame(true);
            break;
        }
        if (startsWith(answer, 'n')) {
            boggle.setUpGame(false);
            break;
        }
        std::cout << "'" << answer << "' is not a valid response!" << endl;
    }

    boggle.startGame();
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
