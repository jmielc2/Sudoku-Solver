#include "Sudoku.hpp"

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    PuzzleData_t SudokuPuzzle::generatePuzzleData(const std::string& puzzle) const {
        return PuzzleData_t{
            Option_t{{1, 0}, 3},
            Option_t{{2, 0}, 4},
            Option_t{{0, 1}, 4},
            Option_t{{3, 1}, 2},
            Option_t{{0, 2}, 1},
            Option_t{{3, 2}, 3},
            Option_t{{1, 3}, 2},
            Option_t{{2, 3}, 1}
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
