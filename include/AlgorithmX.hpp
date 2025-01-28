#pragma once

#include "Sudoku.hpp"
#include <vector>

namespace sdku {
    class AlgorithmX {
    private:
        void reset();
    public:
        AlgorithmX();
        explicit AlgorithmX(const SudokuPuzzle& puzzle);

        void setPuzzle(const SudokuPuzzle& puzzle);
        std::vector<SudokuSolution> solve();
    };
}
