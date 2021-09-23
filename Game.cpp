//
// Created by niko1 on 10.09.2021.
//
#include "Game.h"


Game::Game() {
    for (int i = 0; i < 15; ++i) {
        gameState[i] = i + 1;
    }
    std::shuffle(std::begin(gameState), std::prev(std::end(gameState)),std::default_random_engine(std::random_device{}()));
    gameState[15] = 0;
    currentPosition = 15;
    movesNumber = 0;
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

Game::Game(const std::array<ushort,16> gameField) {
    for(int i = 0; i < 16; i++){
        gameState[i] = gameField[i];
    }
    gameState[15] = 0;
    currentPosition = 15;
    movesNumber = 0;
}

std::vector<unsigned short> Game::getAvailableMoves(unsigned short position) {
    return possibleMoves[position];
}

std::vector<unsigned short> Game::getAvailableMoves() const {
    return getAvailableMoves(currentPosition);
}

void Game::makeMove(unsigned short position) {
    auto av= getAvailableMoves();
    if(std::find(av.begin(), av.end(), position) != av.end()){
        movesHistory.push_back(gameState);
        gameState[currentPosition] = gameState[position];
        currentPosition = position;
        gameState[currentPosition] = 0;
        movesNumber++;
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
        printHistory();
    }
    std::cout << "Wow... You won..." << std::endl;
}

bool Game::isFinish() {
    return isFinish(gameState);
}

void Game::printHistory() {
    for(int i = 1; i < movesHistory.size(); i++){
        for(auto x: movesHistory[i]){
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

bool Game::isSolvable() {
    int pos = 0;
    for (; pos < 16; pos++) {
        if (gameState[pos] == 0) {
            break;
        }
    }
    int cnt = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 16; j++) {
            if (gameState[j] && gameState[i] && gameState[i] > gameState[j])
                cnt++;
        }
    }
    if (pos <= 3 || (pos >= 8 && pos <= 11)) {
        return cnt % 2;
    } else {
        return !(cnt % 2);
    }
}

uint Game::pathToPosition(int idealposition, int position) {
    return abs((idealposition/4) - (position/4)) + abs((idealposition % 4) - (position % 4));
}

uint Game::h(std::array<unsigned short, 16> state) {
    uint res = 0;
    for (int i = 0; i < 16; ++i) {
        if(state[i] == 0){
            continue;
        }
        res += pathToPosition(state[i]-1, i);
    }
    return res;
}

std::array<ushort, 16> Game::getStateAfterMove(std::array<unsigned short, 16> node, unsigned short movedPosition) {
    std::array<ushort,16> newNode{};
    for (int i = 0; i < 16; ++i) {
        if(node[i] == 0){
            newNode[i] = node[movedPosition];
            continue;
        }
        newNode[i] = node[i];
    }
    newNode[movedPosition] = 0;
    return newNode;
}

Game::Game(std::string hexString) {
    for(int i = 0; i < 16; i++){
        gameState[i] = hexToUshort(hexString[i]);
        if(gameState[i] == 0){
            currentPosition = i;
        }
    }
    movesNumber = 0;
}
