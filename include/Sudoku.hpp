#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace sdku {
    using Position_t = std::pair<size_t, size_t>;
    using Value_t = size_t;
    using Option_t = std::pair<Position_t, Value_t>;
    using PuzzleData_t = std::vector<Option_t>;

    class SudokuPuzzle {
    private:
        PuzzleData_t puzzle_data;

        PuzzleData_t generatePuzzleData(const std::string&) const;
    public:
        explicit SudokuPuzzle(const std::string&);
        explicit SudokuPuzzle(const PuzzleData_t&);

        inline const PuzzleData_t& puzzleData() const { return puzzle_data; };
    };

    class SudokuSolution {
    private:
        std::string solution;

        std::string generateBoard(const SudokuPuzzle&, const PuzzleData_t&) const;
    public:
        SudokuSolution(const SudokuPuzzle&, const PuzzleData_t&);

        inline const std::string& board() const { return solution; }
    };
}
