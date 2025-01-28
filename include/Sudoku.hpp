#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <string>

namespace sdku {
    using puzzle_data_t = std::vector<std::pair<int, std::int_least8_t>>;

    class SudokuPuzzle {
    private:
        puzzle_data_t puzzle_data;

        puzzle_data_t generatePuzzleData(const std::string& puzzle) const;
    public:
        explicit SudokuPuzzle(const std::string& puzzle);
        explicit SudokuPuzzle(const puzzle_data_t& puzzle);
    };

    class SudokuSolution {
    private:
        std::string solution;

        std::string generateBoard(const SudokuPuzzle& puzzle, const puzzle_data_t& solution) const;
    public:
        SudokuSolution(const SudokuPuzzle& puzzle, const puzzle_data_t& solution);

        inline const std::string& board() const { return solution; }
    };
}
