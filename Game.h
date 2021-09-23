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

    static bool isFinish(std::array<ushort, 16> state){
        for (int i = 0; i < 15; ++i) {
            if(state[i]!= i + 1){
                return false;
            }
        }
        return true;
    }

    void solve(){
        if(!isSolvable()){
            std::cout << "No solution" << std::endl;
            return;
        }
        //std::deque<std::array<ushort, 16>> movesHistory{};
        movesHistory.push_back(gameState);
        uint bound = h(gameState);
        while(true){
            uint t = ida_star(bound);
            if (t == -1){
                std::cout << "good" << std::endl;
                return;
            } else if (t == INT32_MAX){
                std::cout << "bad" << std::endl;
                return;
            }
            bound = t;
        }
    }

    uint ida_star(uint bound){
        std::array<ushort, 16> node = movesHistory.back();
        uint f = movesHistory.size() + h(node);
        if (f > bound){
            return f;
        }
        if(isFinish(node)){
            return -1;
        }
        uint min = INT32_MAX;
        for (std::array<ushort,16> sNode: successors(node)){
            movesHistory.push_back(sNode);
            uint t = ida_star(bound);
            if(t == -1){
                return -1;
            }
            if(t < min){
                min = t;
            }
            movesHistory.pop_back();
        }
        return min;
    }

    static std::vector<std::array<ushort,16>> successors(std::array<ushort,16> node){
        std::vector<std::array<ushort,16>> res {};
        int i = 0;
        for(; i < 16; i++){
            if(node[i] == 0){
                break;
            }
        }
        for (ushort move: getAvailableMoves(i)) {
            res.push_back(getStateAfterMove(node,move));
        }
        return res;
    }

    static std::array<ushort,16> getStateAfterMove(std::array<ushort,16> node, ushort movedPosition);

    static uint pathToPosition(int idealposition, int position);

    // Manhattan distance
    static uint h(std::array<ushort, 16> state);

};


#endif //FIFTEENKI_GAME_H
