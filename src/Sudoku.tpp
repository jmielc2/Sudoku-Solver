#include "Sudoku.hpp"

#include "util.hpp"

#include <algorithm>
#include <format>

namespace sdku {
    /*
    * Sudoku Puzzle
    */

    template<size_t D>
    PuzzleData_t SudokuPuzzle<D>::generatePuzzleData(const std::string& puzzle) const {
        PuzzleData_t puzzle_data{};
        puzzle_data.reserve(puzzle.size());
        size_t x = 0;
        size_t y = 0;
        for (const auto c : puzzle) {
            Value_t value(c);
            if (value > 0 && value <= D) [[unlikely]] {
                puzzle_data.emplace_back(Option_t{{x, y}, value});
            } else if (value > D) [[unlikely]] {
              std::string message = std::format("Sudoku puzzle values must be between 0 and {}", D);
              throw std::runtime_error(message);
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
