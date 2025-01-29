#pragma once

#include "Sudoku.hpp"

#include <vector>
#include <cstdint>
#include <utility>
#include <cmath>

namespace sdku {
    template<size_t D = 9>
    class AlgorithmX {
    private:
        // Types
        using Option =
            std::pair<std::pair<size_t, size_t>, std::uint_least8_t>;

        struct Node {
            size_t up = 0;
            size_t down = 0;
            size_t left = 0;
            size_t right = 0;
            size_t self = 0;
            size_t constraint = 0;
            union {
                Option option;
                size_t count{0};
            };

            void remove(std::vector<Node>&);
            void undo(std::vector<Node>&);
        };

        static_assert(D > 0 && (D == 4 || D == 9));

        // Members
        SudokuPuzzle puzzle;
        std::vector<Node> nodes;
        bool puzzle_set = false;

        static constexpr int dlx_dim_x = D * D * 4;
        static constexpr int dlx_dim_y = (D * D * D) + 1;
        static constexpr size_t num_nodes = dlx_dim_x * dlx_dim_y + 1;

        // Methods
        inline constexpr size_t head() const;
        constexpr std::pair<size_t, size_t> indexToPosition(size_t) const;  
        void reset();
    public:
        // Constructors
        AlgorithmX();
        explicit AlgorithmX(const SudokuPuzzle&);

        // Methods
        void setPuzzle(const SudokuPuzzle&);

        std::vector<SudokuSolution> solve();
    };
}

#include "AlgorithmX.inl"
