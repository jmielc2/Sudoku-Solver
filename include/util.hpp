#pragma once

#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <variant>

namespace sdku {
    using Position_t = std::pair<size_t, size_t>;
    using Value_t = size_t;
    using Option_t = std::pair<Position_t, Value_t>;
    using PuzzleData_t = std::vector<Option_t>;
}

#include "Sudoku.hpp"

namespace sdku {
    template<size_t D> class SudokuPuzzle;

    using Position_t = std::pair<size_t, size_t>;
    using Value_t = size_t;
    using Option_t = std::pair<Position_t, Value_t>;
    using PuzzleData_t = std::vector<Option_t>;

    std::string createEmptyBoard(const size_t D);

    void fillBoard(const size_t D, std::string& board, const PuzzleData_t& puzzle);

    template<class... T>
    inline std::string generateBoard(const size_t D, const T&... puzzle) {
        std::string board = createEmptyBoard(D);
        for (const auto& data : {puzzle...}) {
            fillBoard(D, board, data);
        }
        return board;
    }

    std::variant<SudokuPuzzle<4>, SudokuPuzzle<9>, SudokuPuzzle<16>> readPuzzleFile(const std::string& filename);
}
