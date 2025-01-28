#pragma once

#include "Sudoku.hpp"
#include <vector>

namespace sdku {
    class AlgorithmX {
    private:
        SudokuPuzzle puzzle;

        void reset();
    public:
        AlgorithmX();
        explicit AlgorithmX(const SudokuPuzzle& puzzle);

        void setPuzzle(const SudokuPuzzle& puzzle);
        std::vector<SudokuSolution> solve();
    };
}
