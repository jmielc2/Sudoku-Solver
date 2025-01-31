#include "AlgorithmX.hpp"

#ifndef NDEBUG
#include <print>
#include <iostream>
#include <string>
#endif

namespace sdku {
    template<size_t D>
    constexpr Position_t AlgorithmX<D>::indexToPosition(const size_t index) const {
        const size_t y = index / D;
        return Position_t{index - (y * D), y};
    }

    template<size_t D>
    template<class UnaryFunction>
    void AlgorithmX<D>::configConstraintNode(const Constraint_t constraint_type, const size_t row_start, const size_t y, const Option_t option, UnaryFunction constraint_eval) {
        const size_t i = row_start + std::to_underlying(constraint_type);
        const size_t constraint = constraint_eval(constraint_type);
        Node& node = nodes.at(i);
        Node& constraint_node = nodes.at(constraint);

        node.self = i;
        if (constraint_type == Constraint_t::CELL) [[unlikely]] {
            node.left = i + 3;
        } else {
            node.left = i - 1;
        }
        if (constraint_type == Constraint_t::BOX) [[unlikely]] {
            node.right = i - 3;
        } else {
            node.right = i + 1;
        }
        node.down = constraint;
        node.up = constraint_node.up;
        node.option = option;
        node.constraint = constraint;

        constraint_node.count++;
        constraint_node.up = node.self;
        if (y == 1) [[unlikely]] {
            constraint_node.down = node.self;
        } else {
            nodes.at(node.up).down = node.self;
        }
    }

    template<size_t D>
    void AlgorithmX<D>::removeConstraint(const size_t constraint) {
        Node& constraint_node = nodes.at(constraint);
        nodes.at(constraint_node.left).right = constraint_node.right;
        nodes.at(constraint_node.right).left = constraint_node.left;

        Node* col_node = &nodes.at(constraint_node.down);
        while (col_node != &constraint_node) {
            Node* row_node = &nodes.at(col_node->right);
            while (row_node != col_node) {
                nodes.at(row_node->up).down = row_node->down;
                nodes.at(row_node->down).up = row_node->up;
                nodes.at(row_node->constraint).count--;
                row_node = &nodes.at(row_node->right);
            }
            col_node = &nodes.at(col_node->down);
        }
    }

    template<size_t D>
    void AlgorithmX<D>::addConstraint(const size_t constraint) {
        Node& constraint_node = nodes.at(constraint);
        nodes.at(constraint_node.left).right = constraint;
        nodes.at(constraint_node.right).left = constraint;

        Node* col_node = &nodes.at(constraint_node.up);
        while (col_node != &constraint_node) {
            Node* row_node = &nodes.at(col_node->left);
            while (row_node != col_node) {
                nodes.at(row_node->up).down = row_node->self;
                nodes.at(row_node->down).up = row_node->self;
                nodes.at(row_node->constraint).count++;
                row_node = &nodes.at(row_node->left);
            }
            col_node = &nodes.at(col_node->up);
        }
    }

    template<size_t D>
    size_t AlgorithmX<D>::evalCellConstraint(const Option_t& hint) {
        const Position_t& position = hint.first;
        return position.second * D + position.first;
    }

    template<size_t D>
    size_t AlgorithmX<D>::evalRowConstraint(const Option_t& hint) {
        const size_t& value = hint.second;
        const Position_t& position = hint.first;
        return (D * D) + (D * (value - 1)) + (position.second);
    }

    template<size_t D>
    size_t AlgorithmX<D>::evalColConstraint(const Option_t& hint) {
        const size_t& value = hint.second;
        const Position_t& position = hint.first;
        return (D * D * 2) + (D * (value - 1)) + (position.first);
    }

    template<size_t D>
    size_t AlgorithmX<D>::evalBoxConstraint(const Option_t& hint) {
        const size_t box_dim = std::sqrt(D);
        const size_t& value = hint.second;
        const Position_t& position = hint.first;
        return (D * D * 3) + (D * (value - 1)) + ((position.second + position.first + 2) / box_dim);
    }
    
    template<size_t D>
    void AlgorithmX<D>::reset() {
        // Setup head node
        Node& head_node = nodes.at(head());
        head_node.left = dlx_dim_x - 1;
        head_node.right = 0;

        // Setup constraint nodes
        for (size_t col = 0; col < dlx_dim_x; col++) {
            Node& node = nodes.at(col);
            node.left = col - 1;
            node.right = col + 1;
            node.down = node.up = node.self = node.constraint = col;
            node.count = 0;
        }
        nodes.at(0).left = head();
        nodes.at(dlx_dim_x - 1).right = head();

        // Setup nodes
        const size_t box_dim = std::sqrt(D);
        for (size_t y = 0, row_start = dlx_dim_x; y < dlx_dim_y - 1; y++, row_start += 4) {
            // Meta data used to determine the cell constraint
            const size_t value = (y / (D * D)) + 1;
            const size_t index = y % (D * D);
            const auto position = indexToPosition(index);
            const auto option = std::pair{position, value};

            #ifndef NDEBUG
            std::println("{} : value = {}, index = {}, position = {}", y, value, index, position);
            // if (index == 15) {
            //     std::getchar();
            // }
            #endif

            configConstraintNode(Constraint_t::CELL, row_start, y, option, [index](const Constraint_t) -> size_t {
                return index;
            });
            configConstraintNode(Constraint_t::ROW, row_start, y, option, [value, position](const Constraint_t) -> size_t {
                return (D * D) + (D * (value - 1)) + position.second;
            });
            configConstraintNode(Constraint_t::COL, row_start, y, option, [value, position](const Constraint_t) -> size_t {
                return (D * D * 2) + (D * (value - 1)) + position.first;
            });
            configConstraintNode(Constraint_t::BOX, row_start, y, option, [value, position, box_dim](const Constraint_t) -> size_t {
                return (D * D * 3) + (D * (value - 1)) + ((position.second + position.first + 2) / box_dim);
            });
        }
        std::println("");

        Node* col_node = &nodes.at(nodes.at(head()).right);
        for (size_t x = 0; x < dlx_dim_x + 1; x++) {
            std::println("Constraint {}", col_node->self);
            Node* row_node = &nodes.at(col_node->down);
            while (row_node != col_node) {
                std::println("  {}", row_node->option);
                row_node = &nodes.at(row_node->down);
            }
            std::getchar();
            col_node = &nodes.at(col_node->right);
        }
    }

    template<size_t D>
    size_t AlgorithmX<D>::chooseConstraint() {
        return nodes.at(head()).right;
    }

    template<size_t D>
    void AlgorithmX<D>::printBoard() {
        const size_t length = D * (D + 1);
        std::string board(length, 'X');
        for (const auto& option : current_solution) {
            const auto position = option.first;
            const size_t index = position.second * (D + 1) + position.first;
            board[index] = char(option.second + '0');
        }
        for (const auto& hint : puzzle.puzzleData()) {
            const auto& position = hint.first;
            const size_t index = position.second * (D + 1) + position.first;
            board[index] = char(hint.second + '0');
        }
        for (size_t i = 0; i < D; i++) {
            board[i * (D + 1) + D] = '\n';
        }
        std::println("{}", board);
    }

    template<size_t D>
    void AlgorithmX<D>::solveHelper() {
        Node& head_node = nodes.at(head());
        if (head_node.right == head()) {
            solution.push_back(SudokuSolution{puzzle, current_solution});
            return;
        }
        size_t constraint = chooseConstraint();
        removeConstraint(constraint);
        Node* row_node = &nodes.at(nodes.at(constraint).down);
        while (row_node->self != constraint) {
            current_solution.push_back(row_node->option);

            #ifndef NDEBUG
            std::println("Placing {} at {}", row_node->option.second, row_node->option.first);
            printBoard();
            std::getchar();
            #endif

            Node* col_node = &nodes.at(row_node->right);
            while (col_node != row_node) {
                removeConstraint(col_node->constraint);
                col_node = &nodes.at(col_node->right);
            }
            solveHelper();
            if (solution.size() > 0) {
                return;;
            }
            col_node = &nodes.at(row_node->left);
            while (col_node != row_node) {
                addConstraint(col_node->constraint);
                col_node = &nodes.at(col_node->left);
            }
            current_solution.pop_back();
            row_node = &nodes.at(row_node->down);
        }
        addConstraint(constraint);
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX() :
      puzzle(PuzzleData_t{})
    {
        reset();
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX(const SudokuPuzzle& puzzle) :
      puzzle(puzzle)
    {
        setPuzzle(puzzle);
    }

    template<size_t D>
    void AlgorithmX<D>::setPuzzle(const SudokuPuzzle& puzzle) {
        reset();
        for (const auto& hint : puzzle.puzzleData()) {
            removeConstraint(evalCellConstraint(hint));
            removeConstraint(evalRowConstraint(hint));
            removeConstraint(evalColConstraint(hint));
            removeConstraint(evalBoxConstraint(hint));
        }
        puzzle_set = true;
    }

    template<size_t D>
    std::vector<SudokuSolution> AlgorithmX<D>::solve() {
        if (!puzzle_set) {
            std::println("No puzzle given!");
            return { };
        }
        solveHelper();
        return solution;
    }
};
