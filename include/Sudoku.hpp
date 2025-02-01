#pragma once

#include "util.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <variant>

namespace sdku {
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

    template<class... T>
    inline std::string generateBoard(const size_t D, const T&... puzzle);

    std::variant<SudokuPuzzle<4>, SudokuPuzzle<9>, SudokuPuzzle<16>> readPuzzleFile(const std::string& filename);
}

#include "Sudoku.tpp"
