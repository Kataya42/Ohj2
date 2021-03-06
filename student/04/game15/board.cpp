/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes:
 * Most important method, action does not return anything, it just changes grid
 * inside the method. Constructor depending on the boolean (shuffle) either
 * calls for the creation of the grid using a given vector of ints or puts them
 * through the randomizer (myShuffle) of which then the grid is created.
 * Playing the game is not done from within the object but through calling
 * different methods found in main.cpp
 * EMPTY is not taken from MAX even though the values are the same
 * because their significance is different.
 * */

#include "board.hh"

#include <iomanip>
#include <iostream>

#include <random>

// which number is to be considered the "empty" tile
// must be largest number for isVictor to work properly
const int EMPTY = 16;
const unsigned int PRINT_WIDTH = SIZE + 1;


Board::Board(bool shuffle, std::vector<unsigned int> numbers) {

    // if numbers in vector are to be shuffled,
    // gets seed and randomizes the vector
    if (shuffle) {
        int seed = getSeed();
        myShuffle(numbers, seed);
    // else creates grid using that numbers in that order in the vector
    } else {
        createGrid(numbers);
    }
}

void Board::createGrid(std::vector<unsigned int> numbers) {

    int temp = 0;
    // creates a SIZE x SIZE grid (default 4x4)
    // using the numbers in a vector in order from left to right row by row
    for (unsigned int i = 0; i < SIZE; i++) {
        std::vector<unsigned int> row;
        for (int j = 0; j < SIZE; j++) {
            unsigned count = numbers[temp];
            row.push_back(count);
            temp += 1;
        }
        grid_.push_back(row);
    }
}

int Board::getSeed() {

    std::string seed;
    std::cout << "Enter a seed value or an empty line: ";
    std::getline (std::cin, seed);

    if (seed == "") {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        return time(NULL);
    } else {
        // If the user gave a seed value, use it.
        return stoi(seed);
    }
}

void Board::print() {

    for(unsigned int x = 0; x < SIZE; ++x) {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y) {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            // if number to be printed is not the "EMPTY" number (default 16)
            // it print the number
            if(grid_[x][y]!= EMPTY) {
                std::cout << grid_[x][y];
            // otherwise it prints an "empty" slot, makerd by a dot
            } else {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

bool Board::isSolvable() {

    // copy of the created grid for testing whether the game is solvable
    std::vector<std::vector<unsigned int>> test_grid = grid_;

    // moving the EMPTY number to the lowest row
    for (unsigned int i=0; i < SIZE; i++) {
        for (unsigned int j=0; j < SIZE; j++) {
            // as long as the number is the EMTPY number
            // and we are not on the final row, then move it one space down
            if (test_grid[i][j] == EMPTY && i != SIZE-1) {
                test_grid[i][j] = test_grid[i+1][j];
                test_grid[i+1][j] = EMPTY;
            }
        }
    }

    // Initialize the sum of inversions
    unsigned int inv_sum = 0;

    // Go through each number from 2 to max value and count inversions
    for (unsigned int n = 2; n < MAX; n++) {
        bool found = false;
        // Start from last position, proceed in reverse and
        // count inversions until the target number is found
        unsigned int pos = MAX - 1;
        while(not found) {
            // If target number is found, stop counting
            if (test_grid[pos/SIZE][pos%SIZE] == n) {
                found = true;
            // Inversion found, add to counter
            } else if (test_grid[pos/SIZE][pos%SIZE] < n) {
                // All are added to same sum variable,
                // so the final sum doesn't need
                // separate additon
                inv_sum++;
            }
            // Decrease position
            pos--;
        }
    }

    // If the inverse sum is even, the game is solvable
    if (inv_sum % 2 == 0) {
        std::cout << "Game is solvable: Go ahead!" << std::endl;
        return true;
    // if odd, game is not solvable
    } else {
        std::cout << "Game is not solvable. What a pity." << std::endl;
        return false;
    }
}

void Board::action(char direction,  unsigned int number) {

    // Integers used for error checking
    int I = -1;
    int J = -1;

    for (unsigned int i=0; i < SIZE; i++) {
        for (unsigned int j=0; j < SIZE; j++) {
            // Makes sure the given number is in the grid
            if (grid_[i][j] == number) {
              I = (signed)i;
              J = (signed)j;
            }
        }
    }

    // If its not, does not attempt to move
    // (This should never be the case, as
    // the grid and input is checked separately)
    if (I == -1 || J == -1) {
        std::cout << "Error: number not in grid!" << std::endl;

    // else does the movement in given direction and swaps The places assuming
    // its not out of bounds and is the EMPTY tile/number
    // w = up, s = down, a = left, d = right
    } else {

        if (direction == 'w' && I > 0 && grid_[I-1][J] == EMPTY) {

            grid_[I-1][J] = number;
            grid_[I][J] = EMPTY;

        } else if (direction == 'a' && J > 0 && grid_[I][J-1] == EMPTY) {

            grid_[I][J-1] = number;
            grid_[I][J] = EMPTY;

        } else if (direction == 's' && I < SIZE-1 && grid_[I+1][J] == EMPTY) {

            grid_[I+1][J] = number;
            grid_[I][J] = EMPTY;

        } else if (direction == 'd' && J < SIZE-1 && grid_[I][J+1] == EMPTY) {

            grid_[I][J+1] = number;
            grid_[I][J] = EMPTY;

        // if it was an illegal move
        } else {

            std::cout << "Impossible direction: " << direction << std::endl;
        }
    }
}

bool Board::isVictory() {

    int victory_check = 0;

    for (unsigned int i=0; i < SIZE; i++) {
        for (unsigned int j=0; j < SIZE; j++) {
            // if the previous number in the row is smaller than the subsequent
            // one, add a point towards victory check
            if (j != 0 && grid_[i][j-1] < grid_[i][j]){
                victory_check ++;
            // checks the first numbers on each row for their previous number
            } else if (j == 0 && i != 0 && grid_[i-1][j+3] < grid_[i][j]){
                victory_check ++;
            }
        }
    }

    // if each number is in order, prints victory and returns true
    if (victory_check == MAX - 1) {
        std::cout << "You won!" << std::endl;
        return true;
    } else {
        return false;
    }
}

void Board::myShuffle(std::vector<unsigned int> &numbers, int seed) {

    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);

    for(unsigned int i = 0; i < numbers.size(); ++i) {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers[i];
        // Assigns the numbers to random indexes in the vector
        numbers[i] = numbers[random_index];
        numbers[random_index] = temp;
    }
    createGrid(numbers);
}
