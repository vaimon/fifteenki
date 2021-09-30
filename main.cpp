#include <iostream>
#include <chrono>
#include "Game.h"
#include "WalkingDistance.h"

int main() {
    setlocale(LC_ALL, "Russian");
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    WalkingDistance::load({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},4,4);
//    unsigned short state [15] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//    Game g (state);
    std::cout<< "Database loaded" << std::endl;
    Game g("1234067859ACDEBF");
    g.solve();

//    Game g("0FEDCBA987654321");
//    g.ha();
//    std::vector<std::string> inputs{"F2345678A0BE91CD", "123456789AFB0EDC", "123456789ABCDEF0", "1234067859ACDEBF",
//                                    "5134207896ACDEBF", "16245A3709C8DEBF", "1723068459ACDEBF", "12345678A0BE9FCD",
//                                    "51247308A6BE9FCD", "F2345678A0BE91DC", "75123804A6BE9FCD", "75AB2C416D389F0E",
//                                    "04582E1DF79BCA36", "FE169B4C0A73D852", "D79F2E8A45106C3B", "DBE87A2C91F65034",
//                                    "BAC0F478E19623D5"};
//    for (const auto &s: inputs) {
//        std::cout << s << " => ";
//        Game g(s);
//        auto timerStart = high_resolution_clock::now();
//        g.solve();
//        auto timerEnd = high_resolution_clock::now();
//        duration<double, std::milli> timeAmount = timerEnd - timerStart;
//        std::cout << "Time taken: " << timeAmount.count() / 1000.0 << "s." << std::endl << std::endl;
//    }

//    g.makeMove(11);
//    g.printGame();
//    g.playGame();

    return 0;
}
