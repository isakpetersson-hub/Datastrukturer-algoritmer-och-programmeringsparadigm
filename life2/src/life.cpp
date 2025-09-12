#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

Grid<char> readStartFile( const std::string& fileName );
void printGrid( const Grid<char>& grid );
void tick( Grid<char>& grid );
void animate( Grid<char>& grid );
void handleInput( const char& input, bool& quit, Grid<char>& grid );

int main() {
    clearConsole();
    std::cout << "Welcome to the TDDD86 Game of Life, \n"
                 "a simulation of the lifecycle of a bacteria colony.\n"
                 "Cells (X) live and die by the following rules:\n"
                 " - A cell with 1 or fewer neighbours dies.\n"
                 " - Locations with 2 neighbours remain stable.\n"
                 " - Locations with 3 neighbours will create life.\n"
                 " - A cell with 4 or more neighbours dies.\n\n"
                 "Grid input file name? " << std::ends;

    std::string fileName;
    std::cin >> fileName;

    Grid<char> grid = readStartFile( fileName );

    // Main loop
    bool quit = false;
    char input;

    while( !quit ) {
        printGrid( grid );

        std::cout << "a)nimate, t)ick, q)uit? " << std::ends;
        std::cin >> input;

        handleInput( input, quit, grid );
    }

    std::cout << "Have a nice Life! "  << std::endl;
    pause(500);
    clearConsole();
    return 0;
}


void handleInput( const char& input, bool& quit, Grid<char>& grid ) {
    switch( input ) {
    case 'a':
        animate( grid );
        break;
    case 't':
        tick( grid );
        break;
    case 'q':
        quit = true;
        break;
    default:
        break;
    }
}

void tick( Grid<char>& grid ) {
    // Ait rules for new generations:
    // - 0/1 neighbours, lil bro dies
    // - 2 neighbours, nothin' happens
    // - 3 neighbours, boom life
    // - 4+ neighbours, lil bro dies
    Grid newGrid = grid;

    for( int i = 0; i <grid.nCols; i++ ) {
        for( int j = 0; j < grid.nRows; j++ ) {
            int neighbours = 0;
            for( int y = -1; y <= 1; y++ ) {
                for( int x = -1; x <= 1; x++ ) {
                    if( grid.inBounds(j+y, i+x) && (grid.get(j+y, i+x) == 'X') && !((x == 0) && (y == 0)) ) {
                        neighbours++;
                    }
                }
            }
            //std::cout << "Neighbours for cell: " << i << ", " << j << ": " << neighbours << std::endl;
            switch(neighbours) {
            case 2:
                break;
            case 3:
                newGrid.set(j, i, 'X');
                break;
            default:
                newGrid.set(j, i, '-');
                break;

            }
        }
    }

    grid = newGrid;
}

void animate( Grid<char>& grid ) {
    for( unsigned int i = 0; i < 20; i++ ) {
        tick( grid );
        pause( 200 );
        printGrid( grid );
    }
}

Grid<char> readStartFile( const std::string& fileName ) {
    // Tries to read whatever file is associated with the provided fileName.
    // Returns a Grid object made with data from the file

    std::ifstream fileStream( fileName );
    std::string fileText;
    unsigned int rows, columns;
    rows = columns = 0;

    // First we read rows and columns (always two first lines)
    fileStream >> rows;
    fileStream >> columns;
    std::cout << rows << " awawa " << columns << std::endl;

    Grid<char> grid = Grid<char>(rows, columns);

    for( unsigned int i = 0; i<rows; i++) {
        fileStream >> fileText;
        for( unsigned int j = 0; j < columns; j++) {
            grid.set(i, j, fileText[j]);
        }
    }

    fileStream.close();

    return grid;
}

void printGrid( const Grid<char>& grid ) {
    for( int i = 0; i < grid.numRows(); i++ ) {
        for( int j = 0; j < grid.numCols(); j++ ) {
            std::cout << grid.get( i, j );
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}
