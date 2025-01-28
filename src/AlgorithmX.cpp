#include "AlgorithmX.hpp"

#include <cstdint>
#include <utility>
#include <vector>
#include <memory>

namespace sdku {
    struct Node;

    using Constraint = Node;
    using Option = std::pair<int, std::int_least8_t>;

    struct Node {
        std::weak_ptr<Node> up;
        std::weak_ptr<Node> down;
        std::weak_ptr<Node> left;
        std::weak_ptr<Node> right;
        std::weak_ptr<Constraint> constraint;
        Option option;
    };

    void AlgorithmX::reset() {
        return;
    }

    AlgorithmX::AlgorithmX() : puzzle(puzzle_data_t{}) {
        return;
    }

    AlgorithmX::AlgorithmX(const SudokuPuzzle& puzzle) : puzzle(puzzle) {
        return;
    }

    void AlgorithmX::setPuzzle(const SudokuPuzzle& puzzle) {
        return;
    }

    std::vector<SudokuSolution> AlgorithmX::solve() {
        return { };
    }
}
