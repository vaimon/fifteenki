//
// Created by niko1 on 10.09.2021.
//
#include <random>
#include <algorithm>
#include <functional>

#include "Game.h"

Game::State::State(Game::State *parent) : parent(parent) {}

Game::Game() {
    for (int i = 0; i < 15; ++i) {
        gameState[i] = i + 1;
    }
    std::shuffle(std::begin(gameState), std::prev(std::end(gameState)),std::default_random_engine(std::random_device{}()));
    gameState[15] = 0;
    currentPosition = 15;
    initializeMoves();
}


void Game::printGame() {
    std::cout << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(gameState[4 * i + j] == 0){
                printf("\t   ");
                continue;
            }
            printf("\t%2.d ", gameState[4 * i + j]);
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << std::endl;
}

Game::Game(const unsigned short* gameField) {
    for(int i = 0; i < 16; i++){
        gameState[i] = gameField[i];
    }
    gameState[15] = 0;
    currentPosition = 15;
    initializeMoves();
}


void Game::initializeMoves() {
    possibleMoves.resize(16);
    possibleMoves[0] = {1,4};
    possibleMoves[1] = {0,2,5};
    possibleMoves[2] = {1,3,6};
    possibleMoves[3] = {2,7};
    possibleMoves[4] = {0,5,8};
    possibleMoves[5] = {1,4,6,9};
    possibleMoves[6] = {2,5,7,10};
    possibleMoves[7] = {3,6,11};
    possibleMoves[8] = {4,9,12};
    possibleMoves[9] = {5,8,10,13};
    possibleMoves[10] = {6,9,11,14};
    possibleMoves[11] = {7,10,15};
    possibleMoves[12] = {8,13};
    possibleMoves[13] = {9,12,14};
    possibleMoves[14] = {10,13,15};
    possibleMoves[15] = {11,14};
}

std::vector<unsigned short> Game::getAvailableMoves(unsigned short position) {
    return possibleMoves[position];
}

std::vector<unsigned short> Game::getAvailableMoves() {
    return getAvailableMoves(currentPosition);
}

void Game::makeMove(unsigned short position) {
    auto av= getAvailableMoves();
    if(std::find(av.begin(), av.end(), position) != av.end()){
        gameState[currentPosition] = gameState[position];
        currentPosition = position;
        gameState[currentPosition] = 0;
    } else{
        throw std::exception("You have tried to make an illegal move.");
    }
}

ushort Game::hexToUshort(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default: return -1;
    }
}

char Game::ushortToHex(unsigned short c) {
    switch (c) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: return -1;
    }
}

std::string Game::toHexString() {
    std::stringstream ss;
    for (unsigned short i : gameState) {
        ss << ushortToHex(i);
    }
    return ss.str();
}

void Game::playGame() {
    while(!isFinish()){
        printGame();
        auto av = getAvailableMoves();
        std::cout << "You can move these tiles: ";
        for (int i = 0; i < av.size(); i++) {
            std::cout << i+1 <<") " << gameState[av[i]] << "\t";
        }
        std::cout << "\nWhat do you choose? Insert number of option: ";
        int c;
        std::cin >> c;
        makeMove(av[c-1]);
    }
    std::cout << "Wow... You won..." << std::endl;
}

bool Game::isFinish() {
    for (int i = 0; i < 15; ++i) {
        if(gameState[i]!= i + 1){
            return false;
        }
    }
    return true;
}

Game::Game(std::string hexString) {
    std::cout << "ok" << std::endl;
    for(int i = 0; i < 16; i++){
        gameState[i] = hexToUshort(hexString[i]);
    }
}
