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
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

Board::Board(bool shuffle, std::vector<unsigned int> numbers) {
        if (shuffle){
            int seed = get_seed();
            my_shuffle(numbers, seed);
        } else {
            initialize(numbers);
        }
    }

void Board::initialize(std::vector<unsigned int> numbers) {
    int temp = 0;
    for (int i = 0; i < 4; i++) {
        std::vector<unsigned int> row;
        for (int j = 0; j < 4; j++) {
            unsigned count = numbers.at(temp);
            row.push_back(count);
            temp += 1;
        }
        grid_.push_back(row);
    }
}

int Board::get_seed() {
    std::string seed;
    std::cout << "Enter a seed value or an empty line: ";
    std::getline (std::cin, seed);

    if (seed == "") {
        return time(NULL);
    } else {
        return stoi(seed);
    }
}

void Board::print() {
    for(unsigned int x = 0; x < SIZE; ++x) {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::is_solvable()
{
    std::cout << "Game is solvable: Go ahead! :) " << std::endl;
}


void Board::action(char com,  unsigned int num)
{
    int I = -1;
    int J = -1;

    for (unsigned int i=0; i < 4; i++) {
        for (unsigned int j=0; j < 4; j++) {
            if (grid_[i][j]==num) {
              I = (signed)i;
              J = (signed)j;
            }
        }
    }
    if (I == -1 || J == -1){
        std::cout << "REEEE" << std::endl;
    } else {
        if (com == 'w' && I > 0 && grid_[I-1][J] == 16) {

            grid_[I-1][J] = num;
            grid_[I][J] = 16;

        } else if (com == 'a' && J > 0 && grid_[I][J-1] == 16) {

            grid_[I][J-1] = num;
            grid_[I][J] = 16;

        } else if (com == 's' && I < 3 && grid_[I+1][J] == 16) {

            grid_[I+1][J] = num;
            grid_[I][J] = 16;

        } else if (com == 'd' && J < 3 && grid_[I][J+1] == 16) {

            grid_[I][J+1] = num;
            grid_[I][J] = 16;

        } else {
            std::cout << "impossible move " << com << std::endl;
        }
    }
}

bool Board::victory()
{

    if (grid_[0][0] < grid_[0][1] && grid_[0][2] < grid_[0][3] && grid_ [1][0] <
        grid_[1][1] && grid_[1][2] < grid_[1][3] && grid_[2][0] <
        grid_[2][1] && grid_[2][2] < grid_[2][3] && grid_[2][3] <
        grid_[3][0] && grid_[3][1] < grid_[3][3] && grid_[3][2] < grid_[3][3]){
        std::cout << "You won!" << std::endl;
        return false;
    } else {
        return true;
    }

}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    initialize(numbers);


}

