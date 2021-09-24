//
// Created by niko1 on 10.09.2021.
//


#ifndef FIFTEENKI_GAME_H
#define FIFTEENKI_GAME_H

#define ushort unsigned short
#define uint unsigned int

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <deque>

class Game {
    std::array<ushort, 16> gameState{};
    static inline const std::vector<std::vector<ushort>> possibleMoves{{1,  4},
                                                                       {0,  2,  5},
                                                                       {1,  3,  6},
                                                                       {2,  7},
                                                                       {0,  5,  8},
                                                                       {1,  4,  6,  9},
                                                                       {2,  5,  7,  10},
                                                                       {3,  6,  11},
                                                                       {4,  9,  12},
                                                                       {5,  8,  10, 13},
                                                                       {6,  9,  11, 14},
                                                                       {7,  10, 15},
                                                                       {8,  13},
                                                                       {9,  12, 14},
                                                                       {10, 13, 15},
                                                                       {11, 14}};
    ushort currentPosition;
    ushort movesNumber;
    std::deque<std::array<ushort, 16>> movesHistory{};

    static ushort hexToUshort(char c);

    static char ushortToHex(ushort c);

public:
    Game();

    explicit Game(std::array<ushort, 16> gameField);

    explicit Game(std::string hexString);

    void printGame();

    [[nodiscard]] std::vector<ushort> getAvailableMoves() const;

    static std::vector<ushort> getAvailableMoves(ushort position);

    void makeMove(ushort position);

    std::string toHexString();

    bool isFinish();

    void playGame();

    void printHistory();

    // https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
    bool isSolvable();

    static bool isFinish(std::array<ushort, 16> state);

    void solve();

    uint ida_star(uint bound);

    static std::vector<std::array<ushort,16>> successors(std::array<ushort,16> node);

    static std::array<ushort,16> getStateAfterMove(std::array<ushort,16> node, ushort movedPosition);

    static uint pathToPosition(int idealposition, int position);


    static uint computeLinearConflicts(std::array<ushort, 16> state){
        uint res = 0;
        for (int i = 0; i < 4; ++i) {
            int skip = 4;
            for (int j = 0; j < 3; ++j) {
                if(j == skip){
                    continue;
                }
                for (int k = j + 1; k < 4; ++k) {
                    if(state[4*i + k] == 0 || k == skip){
                        continue;
                    }
                    if(state[4*i + j] > state[4*i + k]){
                        skip = k;
                        //std::cout<< (4*i + j) << "(" << state[4*i + j] << ") => " << (4*i + k) << "(" << state[4*i + k] << ")" << "skip = " << skip << std::endl;
                        res +=2;
                        break;
                    }
                }
            }
        }
        return res;
    }

    void ha(){
        std::cout << computeLinearConflicts(gameState) << std::endl;
    }

    // Manhattan distance
    static uint h(std::array<ushort, 16> state);

};


#endif //FIFTEENKI_GAME_H
