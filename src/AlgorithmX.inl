#include "AlgorithmX.hpp"

#ifndef NDEBUG
#include <print>
#endif

namespace sdku {
    template<size_t D>
    void AlgorithmX<D>::Node::remove(std::vector<Node>& nodes) {
        nodes.at(left).right = right;
        nodes.at(right).left = left;
    }

    template<size_t D>
    void AlgorithmX<D>::Node::undo(std::vector<Node>& nodes) {
        nodes.at(left).right = self;
        nodes.at(right).left = self;
    }

    template<size_t D>
    inline constexpr size_t AlgorithmX<D>::head() const { return num_nodes - 1; }

    template<size_t D>
    inline constexpr std::pair<size_t, size_t> AlgorithmX<D>::indexToPosition(size_t index) const {
        return {0, 0};
    }

    template<size_t D>
    void AlgorithmX<D>::reset() {
        Node& head_node = nodes.at(head());
        head_node.left = dlx_dim_x - 1;
        head_node.right = 0;

        // Setup nodes
        size_t row_start = dlx_dim_x;
        for (size_t y = 1; y < dlx_dim_y; y++) {
            for (size_t x = 0; x < dlx_dim_x; x++) {
                const size_t i = x + row_start;
                Node& node = nodes.at(i);
                node.left = i - 1;
                node.right = i + 1;
                node.down = i + dlx_dim_x;
                node.up = i - dlx_dim_x;
                node.self = i;
                node.constraint = x;
                node.option = {};  // TODO: based on current row, what is the option?
            }
            const size_t row_end = row_start + dlx_dim_x - 1;
            Node& start_node = nodes.at(row_start);
            Node& end_node = nodes.at(row_end);
            start_node.left = row_end;
            end_node.right = row_start;
            row_start = row_end + 1;
        }

        // Setup constraint nodes
        for (size_t col = 0; col < dlx_dim_x; col++) {
            Node& node = nodes.at(col);
            node.left = col - 1;
            node.right = col + 1;
            node.down = col + dlx_dim_x;
            node.up = col + (dlx_dim_x * (dlx_dim_y - 1));
            node.self = col;
            node.count = dlx_dim_y - 1;

            nodes.at(node.up).down = col;
        }
        nodes.at(0).left = head();
        nodes.at(dlx_dim_x - 1).right = head();

#ifndef NDEBUG
        Node* node = &head_node;
        node = &nodes.at(node->right);
        while (node != &head_node) {
            node = &nodes.at(node->right);
        }
        node = &nodes.at(node->left);
        while (node != &head_node) {
            node = &nodes.at(node->left);
        }
        std::println("Head loops left and right!");

        for (int i = 0; i < dlx_dim_x; i++) {
            Node* col = &nodes.at(i);
            node = &nodes.at(col->down);
            while (node != col) {
                col = &nodes.at(col->down);
            }
            node = &nodes.at(col->up);
            while (node != col) {
                col = &nodes.at(col->up);
            }
        }
        std::println("Columns loop up and down!");

        for (int i = 0; i < dlx_dim_y; i++) {
            Node* row = &nodes.at(dlx_dim_x);
            node = &nodes.at(row->right);
            while (node != row) {
                node = &nodes.at(node->right);
            }
            node = &nodes.at(row->left);
            while (node != row) {
                node = &nodes.at(node->left);
            }
        }
        std::println("Rows loop right and left!\n");
#endif
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX() :
      puzzle(puzzle_data_t{}),
      nodes(num_nodes)
    {
        reset();
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX(const SudokuPuzzle& puzzle) :
      puzzle(puzzle),
      nodes(num_nodes)
    {
        setPuzzle(puzzle);
#ifndef NDEBEG
        std::println("Size of node - {} bytes", sizeof(Node));
        std::println("Num Node - {} nodes", num_nodes);
        std::println("Size of class - {} bytes\n", sizeof(AlgorithmX) + num_nodes * sizeof(Node));
#endif
    }

    template<size_t D>
    void AlgorithmX<D>::setPuzzle(const SudokuPuzzle& puzzle) {
        reset();
        for (const auto& hint : puzzle.puzzleData()) {

        }
        puzzle_set = true;
    }

    template<size_t D>
    std::vector<SudokuSolution> AlgorithmX<D>::solve() {
        if (!puzzle_set) {
            std::println("No puzzle given!");
            return { };
        }
        return { };
    }
}
