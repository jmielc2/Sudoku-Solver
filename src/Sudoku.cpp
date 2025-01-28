#include "Sudoku.hpp"

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    puzzle_data_t SudokuPuzzle::generatePuzzleData(const std::string& puzzle) const {
        return puzzle_data_t{};
    }

    SudokuPuzzle::SudokuPuzzle(const std::string& puzzle) : puzzle_data(generatePuzzleData(puzzle)) {
        return;
    }

    SudokuPuzzle::SudokuPuzzle(const puzzle_data_t& puzzle) : puzzle_data(puzzle) {
        return;
    }

    /*
    * SudokuSolution
    */

    std::string SudokuSolution::generateBoard(const SudokuPuzzle& puzzle, const puzzle_data_t& solution) const {
        return "Solution\n";
    }

    SudokuSolution::SudokuSolution(const SudokuPuzzle& puzzle, const puzzle_data_t& solution) : solution(generateBoard(puzzle, solution)) {
        return;
    }
}
