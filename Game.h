//
// Created by niko1 on 10.09.2021.
//


#ifndef FIFTEENKI_GAME_H
#define FIFTEENKI_GAME_H

#define ushort unsigned short

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Game {
    ushort gameState[16]{};
    static std::vector<std::vector<ushort>> possibleMoves;
    ushort currentPosition;

    static void initializeMoves();

    static ushort hexToUshort(char c);

    static char ushortToHex(ushort c);

public:
    Game();

    explicit Game(const ushort* gameField);

    explicit Game(std::string hexString);

    void printGame();

    std::vector<ushort> getAvailableMoves();
    static std::vector<ushort> getAvailableMoves(ushort position);

    void makeMove(ushort position);

    std::string toHexString();

    bool isFinish();

    void playGame();
};


#endif //FIFTEENKI_GAME_H
