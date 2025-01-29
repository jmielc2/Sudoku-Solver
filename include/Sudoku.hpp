#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace sdku {
    using puzzle_data_t =
        std::vector<std::pair<std::pair<size_t, size_t>, std::uint_least8_t>>;

    class SudokuPuzzle {
    private:
        puzzle_data_t puzzle_data;

        puzzle_data_t generatePuzzleData(const std::string&) const;
    public:
        explicit SudokuPuzzle(const std::string&);
        explicit SudokuPuzzle(const puzzle_data_t&);

        inline const puzzle_data_t& puzzleData() const { return puzzle_data; };
    };

    class SudokuSolution {
    private:
        std::string solution;

        std::string generateBoard(const SudokuPuzzle&, const puzzle_data_t&) const;
    public:
        SudokuSolution(const SudokuPuzzle&, const puzzle_data_t&);

        inline const std::string& board() const { return solution; }
    };
}
