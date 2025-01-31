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
        enum class Constraint_t : size_t {
            CELL = 0,
            ROW  = 1,
            COL  = 2,
            BOX  = 3
        };

        struct Node {
            size_t left = 0;
            size_t right = 0;
            size_t up = 0;
            size_t down = 0;
            size_t self = 0;
            size_t constraint = 0;
            union {
                Option_t option;
                size_t count{0};
            };
        };

        static_assert(D > 0 && (D == 4 || D == 9 || D == 16));

        // Constants
        static constexpr size_t dlx_dim_x = D * D * 4;
        static constexpr size_t dlx_dim_y = (D * D * D) + 1;
        static constexpr size_t num_nodes = dlx_dim_x + ((dlx_dim_y - 1) * 4) + 1;


        // Members
        SudokuPuzzle puzzle;
        std::array<Node, num_nodes> nodes;
        PuzzleData_t current_solution;
        std::vector<SudokuSolution> solution;
        bool puzzle_set = false;

        // Methods
        inline constexpr size_t head() const { return num_nodes - 1; };
        constexpr Position_t indexToPosition(const size_t) const;
        template<class UnaryFunction>
        void configConstraintNode(const Constraint_t, const size_t, const size_t, const Option_t, UnaryFunction);
        void removeConstraint(const size_t);
        void addConstraint(const size_t);
        size_t evalCellConstraint(const Option_t&);
        size_t evalRowConstraint(const Option_t&);
        size_t evalColConstraint(const Option_t&);
        size_t evalBoxConstraint(const Option_t&);
        void reset();
        size_t chooseConstraint();
        void printBoard();
        void solveHelper();
    public:
        // Constructors
        AlgorithmX();
        explicit AlgorithmX(const SudokuPuzzle&);

        // Methods
        void setPuzzle(const SudokuPuzzle&);

        std::vector<SudokuSolution> solve();
    };
};

#include "AlgorithmX.inl"
