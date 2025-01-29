#pragma once

#include "AlgorithmX.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

namespace sdku {
    template<size_t D>
    constexpr int AlgorithmX<D>::wrapX(int x) const {
        if (x >= dlx_dim_x) {
            x %= dlx_dim_x;
        } else if (x < 0) {
            do {
                x += dlx_dim_x;
            } while (x < 0);
        }
        return x;
    }

    template<size_t D>
    constexpr int AlgorithmX<D>::wrapY(int y) const {
        if (y >= dlx_dim_y) {
            y %= dlx_dim_y;
        } else if (y < 0) {
            do {
                y += dlx_dim_y;
            } while (y < 0);
        }
        return y;
    }

    template<size_t D>
    constexpr size_t AlgorithmX<D>::calcIndex(int x, int y) const {
        x = wrapX(x);
        y = wrapY(y);
        return size_t(x + y * dlx_dim_x);
    }

    template<size_t D>
    void AlgorithmX<D>::reset() {
        Node& head_node = nodes.at(head);
        head_node.left = dlx_dim_x - 1;
        head_node.right = 0;

        // Setup constraint nodes
        for (size_t col = 0; col < dlx_dim_x; col++) {
            Node& node = nodes.at(col);
            node.left = col - 1;
            node.right = col + 1;
            node.down = col + dlx_dim_x;
            node.up = col + (dlx_dim_x * (dlx_dim_y - 1));
            node.count = dlx_dim_y - 1;
        }
        nodes.at(0).left = head;
        nodes.at(dlx_dim_x - 1).right = head;

        // Setup nodes
        size_t row_start = dlx_dim_x;
        for (size_t y = 1; y < dlx_dim_y; y++) {
            for (size_t x = 0; x < dlx_dim_x; x++) {
                const size_t i = x + row_start;
                Node& node = nodes.at(i);
                node.left = i - 1;
                node.right = i + 1;
                node.up = i - dlx_dim_x;
                node.down = i - dlx_dim_x;
            }
            const size_t row_end = row_start + dlx_dim_x - 1;
            Node& start_node = nodes.at(row_start);
            Node& end_node = nodes.at(row_end);
            start_node.left = row_end;
            end_node.right = row_start;
            row_start = row_end + 1;
        }

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
        std::cout << "Head loops left and right!\n";

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
        std::cout << "Columns loop up and down!\n";

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
        std::cout << "Rows loop right and left!\n";
#endif
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX() :
      puzzle(puzzle_data_t{}),
      nodes(num_nodes),
      head(num_nodes - 1)
    {
        reset();
    }

    template<size_t D>
    AlgorithmX<D>::AlgorithmX(const SudokuPuzzle& puzzle) :
      puzzle(puzzle),
      nodes(num_nodes),
      head(num_nodes - 1)
    {
        setPuzzle(puzzle);
    }

    template<size_t D>
    void AlgorithmX<D>::setPuzzle(const SudokuPuzzle& puzzle) {
        reset();
    }

    template<size_t D>
    std::vector<SudokuSolution> AlgorithmX<D>::solve() {
        return { };
    }
}
