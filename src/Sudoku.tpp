#include "Sudoku.hpp"

#include "util.hpp"

#include <algorithm>

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    template<size_t D>
    PuzzleData_t SudokuPuzzle<D>::generatePuzzleData(const std::string& puzzle) const {
        if (puzzle.size() != D * D) {
            throw std::runtime_error("Given puzzle dimensions are invalid.");
        }
        PuzzleData_t puzzle_data;
        size_t x = 0;
        size_t y = 0;
        for (const char& c : puzzle) {
            size_t value  = c - '0';
            if (value > 0 && value <= D) {
                puzzle_data.push_back(Option_t{{x, y}, value});
            }
            x++;
            if (x == D) [[unlikely]] {
                x = 0;
                y++;
            }
        };
        return puzzle_data;
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
