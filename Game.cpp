//
// Created by niko1 on 10.09.2021.
//
#include "Game.h"
#include "WalkingDistance.h"


Game::Game() {
    for (int i = 0; i < 15; ++i) {
        gameState[i] = i + 1;
    }
    std::shuffle(std::begin(gameState), std::prev(std::end(gameState)),
                 std::default_random_engine(std::random_device{}()));
    gameState[15] = 0;
    currentPosition = 15;
    movesNumber = 0;
}


void Game::printGame() {
    std::cout << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (gameState[4 * i + j] == 0) {
                printf("\t   ");
                continue;
            }
            printf("\t%2.d ", gameState[4 * i + j]);
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << std::endl;
}

Game::Game(const std::array<ushort, 16> gameField) {
    for (int i = 0; i < 16; i++) {
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
    return {};
}

void Game::makeMove(unsigned short position) {
    auto av = getAvailableMoves();
    if (std::find(av.begin(), av.end(), position) != av.end()) {
        movesHistory.push_back(gameState);
        gameState[currentPosition] = gameState[position];
        currentPosition = position;
        gameState[currentPosition] = 0;
        movesNumber++;
    } else {
        throw std::exception("You have tried to make an illegal move.");
    }
}

ushort Game::hexToUshort(char c) {
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return -1;
    }
}

char Game::ushortToHex(unsigned short c) {
    switch (c) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return -1;
    }
}

std::string Game::toHexString(std::array<ushort, 16> gameField) {
    std::stringstream ss;
    for (unsigned short i: gameField) {
        ss << ushortToHex(i);
    }
    return ss.str();
}

void Game::playGame() {
    while (!isFinish()) {
        printGame();
        auto av = getAvailableMoves();
        std::cout << "You can move these tiles: ";
        for (int i = 0; i < av.size(); i++) {
            std::cout << i + 1 << ") " << gameState[av[i]] << "\t";
        }
        std::cout << "\nWhat do you choose? Insert number of option: ";
        int c;
        std::cin >> c;
        makeMove(av[c - 1]);
        printHistory();
    }
    std::cout << "Wow... You won..." << std::endl;
}

bool Game::isFinish() {
    return isFinish(gameState);
}

void Game::printHistory() {
    for (int i = 1; i < movesHistory.size(); i++) {
        for (auto x: movesHistory[i]) {
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
    return abs((idealposition / 4) - (position / 4)) + abs((idealposition % 4) - (position % 4));
}

uint Game::manhattan_h(std::array<unsigned short, 16> state) {
    uint res = 0;
    for (int i = 0; i < 16; ++i) {
        if (state[i] == 0) {
            continue;
        }
        res += pathToPosition(state[i] - 1, i);
    }
    res += computeLinearConflicts(state);
    return res;
}

std::tuple<std::array<ushort, 16>,uint,uint> Game::getStateAfterMove(std::array<unsigned short, 16> node, unsigned short movedPosition) {
    std::array<ushort, 16> newNode{};
    uint rowIndex = 0, colIndex = 0;
    for (int i = 0; i < 16; ++i) {
        if (node[i] == 0) {
            newNode[i] = node[movedPosition];

            if(movedPosition - 4 == i){
                rowIndex = WalkingDistance::edgesDown[wdRowIndex]
                [WalkingDistance::row[newNode[i]]];
            } else if(movedPosition + 4 == i){
                rowIndex = (WalkingDistance::edgesUp[wdRowIndex]
                [WalkingDistance::row[newNode[i]]]);
            } else if(movedPosition - 1 == i){
                colIndex = (WalkingDistance::edgesDown[wdColIndex]
                [WalkingDistance::col[newNode[i]]]);
            } else if(movedPosition + 1 == i){
                colIndex = (WalkingDistance::edgesUp[wdColIndex]
                                     [WalkingDistance::col[newNode[i]]]);
            }

            continue;
        }
        newNode[i] = node[i];
    }
    newNode[movedPosition] = 0;
    return std::make_tuple(newNode,wdRowIndex,wdColIndex);
}

void Game::solve() {
    if (!isSolvable()) {
        std::cout << "No solution" << std::endl;
        return;
    }
    //std::deque<std::array<ushort, 16>> movesHistory{};
    movesHistory.push_back(gameState);
    wdRowIndex = (WalkingDistance::getIndex(gameState));
    wdColIndex = (WalkingDistance::getIndex(gameState,false));

    uint bound = h(gameState);
    while (true) {
        uint t = ida_star(bound, 0);
        if (t == -1) {
            std::cout << "Number of moves: " << movesHistory.size() - 1 << std::endl;
            return;
        } else if (t == INT32_MAX) {
            std::cout << "Well, congratulations, everything is screwed up." << std::endl;
            return;
        }
        bound = t;
    }
}

uint Game::ida_star(unsigned int bound, uint g) {
    std::array<ushort, 16> node = movesHistory.back();
    // uint g = movesHistory.size();
    uint f = g + h(node);
    if (f > bound) {
        return f;
    }
    if (isFinish(node)) {
        return -1;
    }
    uint min = INT32_MAX;
    for (std::tuple<std::array<ushort, 16>, uint, uint> tupleNode: successors(node)) {
        auto& [sNode, rowInd, colInd] = tupleNode;
        long long hash = hashState(sNode);
        if (previousStates.find(hash) == previousStates.end() || g <= previousStates[hash]) {
            previousStates[hash] = g;
        } else {
            continue;
        }
        movesHistory.push_back(sNode);
        wdRowIndex = rowInd;
        wdColIndex = colInd;
        uint t = ida_star(bound, g + 1);
        if (t == -1) {
            return -1;
        }
        if (t < min) {
            min = t;
        }
        movesHistory.pop_back();
    }
    return min;
}

std::vector<std::tuple<std::array<ushort, 16>,uint,uint>> Game::successors(std::array<unsigned short, 16> node) {
    std::vector<std::tuple<std::array<ushort, 16>,uint,uint>> res{};
    int i = 0;
    for (; i < 16; i++) {
        if (node[i] == 0) {
            break;
        }
    }
    for (ushort move: getAvailableMoves(i)) {
        res.push_back(getStateAfterMove(node, move));
    }
    return res;
}

bool Game::isFinish(std::array<unsigned short, 16> state) {
    for (int i = 0; i < 15; ++i) {
        if (state[i] != i + 1) {
            return false;
        }
    }
    return true;
}

uint Game::computeLinearConflicts(std::array<unsigned short, 16> state) {
    uint res = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!(((state[4 * i + j] - 1) >= 4 * i) && ((state[4 * i + j] - 1) < 4 * (i + 1)))) {
                continue;
            }
            for (int k = j + 1; k < 4; ++k) {
                if ((((state[4 * i + k] - 1) >= 4 * i) && ((state[4 * i + k] - 1) < 4 * (i + 1)))) {
                    if (state[4 * i + j] > state[4 * i + k]) {
                        res += 2;
                    }
                }
            }
        }
    }

//        for (int i = 0; i < 3; ++i) {
//            for (int j = 0; j < 4; ++j) {
//                if((state[4 * i + j] - 1 - j) % 4 != 0){
//                    continue;
//                }
//                for (int k = i + 1; k < 4; ++k) {
//                    if((state[4 * k + j] - 1 - j) % 4 == 0){
//                        if(state[4*i + j] > state[4*k + j]){
//                            res += 2;
//                        }
//                    }
//                }
//            }
//        }
    return res;
}

long long Game::hashState(std::array<unsigned short, 16> state) {
    long long hash = 0;
    int shift = 0;
    for (int i = state.size() - 1; i >= 0; i--) {
        auto shifted = ((long long) state[i]) << shift;
        hash += shifted;
        shift += 4;
    }
    return hash;
}

uint Game::getRowConflicts(std::array<unsigned short, 16> state) {
    uint cnt = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = i; j < 16; j++) {
            if (state[j] && state[i] && state[i] >= state[j])
                cnt++;
        }
    }
    return cnt;
}

uint Game::getColConflicts(std::array<unsigned short, 16> state) {
    std::array<ushort, 16> transponedState = {state[0], state[4], state[8], state[12], state[1], state[5], state[9],
                                              state[13], state[2], state[6], state[10], state[14], state[3], state[7],
                                              state[11], state[15]};
    return getRowConflicts(transponedState);
}

uint Game::invertDistance_h(std::array<unsigned short, 16> state) {
    uint horizontal = getRowConflicts(state);
    uint vertical = getColConflicts(state);
    return (horizontal / 3 + horizontal % 3) + (vertical / 3 + vertical % 3);
}

uint Game::h(std::array<unsigned short, 16> state) {
    return  walkingDistance_h(state);
}

uint Game::walkingDistance_h(std::array<unsigned short, 16> state) {
    return WalkingDistance::costs[wdRowIndex] + WalkingDistance::costs[wdColIndex];
}

Game::Game(std::string hexString) {
    for (int i = 0; i < 16; i++) {
        gameState[i] = hexToUshort(hexString[i]);
        if (gameState[i] == 0) {
            currentPosition = i;
        }
    }
    movesNumber = 0;
}
