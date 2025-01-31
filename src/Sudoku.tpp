#include "Sudoku.hpp"

#include "util.hpp"

#include <algorithm>

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    template<size_t D>
    PuzzleData_t SudokuPuzzle<D>::generatePuzzleData(const std::string& puzzle) const {
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

    template<size_t D>
    SudokuPuzzle<D>::SudokuPuzzle(const std::string& puzzle) :
      puzzle_data(generatePuzzleData(puzzle)),
      puzzle(generateBoard(D, puzzle_data))
    { }

    template<size_t D>
    SudokuPuzzle<D>::SudokuPuzzle(const PuzzleData_t& puzzle) :
      puzzle_data(puzzle),
      puzzle(generateBoard(D, puzzle))
    { }

    /*
    * Sudoku Solution
    */

    template<size_t D>
    SudokuSolution<D>::SudokuSolution(const PuzzleData_t& puzzle, const PuzzleData_t& solution) :
      solution(generateBoard(D, puzzle, solution))
    { }
}
