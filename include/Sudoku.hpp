#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace sdku {
    using Position_t = std::pair<size_t, size_t>;
    using Value_t = size_t;
    using Option_t = std::pair<Position_t, Value_t>;
    using PuzzleData_t = std::vector<Option_t>;

    template<size_t D = 9>
    class SudokuPuzzle {
    private:
        PuzzleData_t puzzle_data;
        std::string puzzle;

        PuzzleData_t generatePuzzleData(const std::string&) const;
    public:
        explicit SudokuPuzzle(const std::string&);
        explicit SudokuPuzzle(const PuzzleData_t&);

        inline const std::string& board() const { return puzzle; };
        inline const PuzzleData_t& puzzleData() const { return puzzle_data; };
    };

    template<size_t D = 9>
    class SudokuSolution {
    private:
        const std::string solution;

    public:
        SudokuSolution(const PuzzleData_t&, const PuzzleData_t&);

        inline const std::string& board() const { return solution; }
    };
}

#include "Sudoku.tpp"
