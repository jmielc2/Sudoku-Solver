#include "AlgorithmX.hpp"

#include <print>
#include <string>
#include <vector>

namespace sdku {
    template<size_t D>
    constexpr Position_t AlgorithmX<D>::indexToPosition(const size_t index) const {
        const size_t y = index / D;
        return Position_t{index - (y * D), y};
    }

    template<size_t D>
    void AlgorithmX<D>::configConstraintNode(const Constraint_t constraint_type, const size_t row_start, const size_t y, const Option_t& option, size_t (AlgorithmX<D>::*constraint_eval)(const Option_t&)) {
        const size_t i = row_start + std::to_underlying(constraint_type);
        const size_t constraint = (this->*constraint_eval)(option);
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
        if (y == 0) [[unlikely]] {
            constraint_node.down = node.self;
        } else {
            nodes.at(node.up).down = node.self;
        }
    }

    template<size_t D>
    void AlgorithmX<D>::removeConstraint(const size_t constraint) {
        nodes.at(head()).count--;
        const Node& constraint_node = nodes.at(constraint);
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
        nodes.at(head()).count++;
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
        return (D * D * 3) + (D * (value - 1)) + (position.second / box_dim) * box_dim + (position.first / box_dim);
    }
    
    template<size_t D>
    void AlgorithmX<D>::reset() {
        // Setup head node
        Node& head_node = nodes.at(head());
        head_node.left = dlx_dim_x - 1;
        head_node.right = 0;
        head_node.count = dlx_dim_x;

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
        for (size_t y = 0, row_start = dlx_dim_x; y < dlx_dim_y - 1; y++, row_start += 4) {
            // Meta data used to determine the cell constraint
            const size_t value = (y / (D * D)) + 1;
            const size_t index = y % (D * D);
            const auto position = indexToPosition(index);
            const auto option = std::pair{position, value};

            configConstraintNode(Constraint_t::CELL, row_start, y, option, &AlgorithmX<D>::evalCellConstraint);
            configConstraintNode(Constraint_t::ROW, row_start, y, option, &AlgorithmX<D>::evalRowConstraint);
            configConstraintNode(Constraint_t::COL, row_start, y, option, &AlgorithmX<D>::evalColConstraint);
            configConstraintNode(Constraint_t::BOX, row_start, y, option, &AlgorithmX<D>::evalBoxConstraint);
        }
    }

    template<size_t D>
    size_t AlgorithmX<D>::chooseConstraint() {
        Node* head_node = &nodes.at(head());
        std::vector<Node*> sorted_nodes{};
        sorted_nodes.reserve(head_node->count);
        Node* col_node = &nodes.at(head_node->right);
        while (col_node != head_node) {
            sorted_nodes.push_back(col_node);
            col_node = &nodes.at(col_node->right);
        }

        std::sort(sorted_nodes.begin(), sorted_nodes.end(), [](const auto& a, const auto& b) {
            return a->count < b->count;
        });
        return sorted_nodes.front()->self;
    }

    #ifndef NDEBUG
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
    #endif

    template<size_t D>
    void AlgorithmX<D>::solveHelper(const int level) {
        #ifndef NDEBUG
        std::println("Solve Level: {}", level);
        #endif
        Node& head_node = nodes.at(head());
        if (head_node.right == head()) {
            #ifndef NDEBUG
            std::println("Solution found!");
            #endif
            solution.push_back(SudokuSolution<D>{puzzle.puzzleData(), current_solution});
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
            solveHelper(level + 1);
            #ifndef NDEBUG
            std::println("Backtracking to Level: {}", level);
            #endif
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
    { }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX(const SudokuPuzzle<D>& puzzle) :
      puzzle(puzzle)
    {
        setPuzzle(puzzle);
    }

    template<size_t D>
    void AlgorithmX<D>::setPuzzle(const SudokuPuzzle<D>& puzzle) {
        this->puzzle = puzzle;
        puzzle_set = true;
    }

    template<size_t D>
    std::vector<SudokuSolution<D>> AlgorithmX<D>::solve() {
        reset();
        for (const auto& hint : puzzle.puzzleData()) {
            removeConstraint(evalCellConstraint(hint));
            removeConstraint(evalRowConstraint(hint));
            removeConstraint(evalColConstraint(hint));
            removeConstraint(evalBoxConstraint(hint));
        }
        if (!puzzle_set) {
            std::println("No puzzle given!");
            return { };
        }
        solveHelper(0);
        return solution;
    }
};
