#include "Util.h"

#include <algorithm>


std::vector<int> combine(const std::vector<std::vector<int>>& grids) {
    std::vector<int> solution(grids[0].size(), 0);
    for (auto& grid : grids) {
        assertm(grid.size() == solution.size(), "Mismatching pattern sizes");
        for (std::size_t i = 0; i < grid.size(); i++) {
            if (grid[i] != 0) {
                solution[i] = grid[i];
            }
        }
    }
    return solution;
}

int getBlank(const std::vector<int>& board) {
    auto it = std::find(board.cbegin(), board.cend(), 0);
    assertm(it != board.cend(), "Blank must exist in board");
    return std::distance(board.cbegin(), it);
}

