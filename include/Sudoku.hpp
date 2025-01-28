#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <ostream>

namespace sdku {
    using puzzle_t = std::vector<std::pair<int, std::int_least8_t>>;

    class SudokuPuzzle {
    private:
        puzzle_t puzzle_data;
    public:
        SudokuPuzzle() = default;
        explicit SudokuPuzzle(const std::string& puzzle);
        explicit SudokuPuzzle(const puzzle_t& puzzle);
    };

    class SudokuSolution {
    private:
        std::string solution;

        std::string generatePuzzle() const;
    public:
        SudokuSolution(const SudokuPuzzle& puzzle, const puzzle_t& solution);
        friend std::ostream& operator<<(std::ostream& out, const SudokuSolution& solution);
    };
}
