#include "Sudoku.hpp"

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    PuzzleData_t SudokuPuzzle::generatePuzzleData(const std::string& puzzle) const {
        return PuzzleData_t{
            Option_t{{2, 0}, 3},
            Option_t{{2, 1}, 1},
            Option_t{{3, 2}, 1},
            Option_t{{0, 3}, 3},
            Option_t{{2, 3}, 2}
        };
    }

    SudokuPuzzle::SudokuPuzzle(const std::string& puzzle) :
      puzzle_data(generatePuzzleData(puzzle))
    {
        return;
    }

    SudokuPuzzle::SudokuPuzzle(const PuzzleData_t& puzzle) :
      puzzle_data(puzzle)
    {
        return;
    }

    /*
    * Sudoku Solution
    */

    std::string SudokuSolution::generateBoard(const SudokuPuzzle& puzzle, const PuzzleData_t& solution) const {
        return "Solution\n";
    }

    SudokuSolution::SudokuSolution(const SudokuPuzzle& puzzle, const PuzzleData_t& solution) :
      solution(generateBoard(puzzle, solution))
    {
        return;
    }
}
