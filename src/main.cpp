#include <print>
#include <string>

#include "AlgorithmX.hpp"


int main() {
    try {
        // Setup
        const size_t puzzle_dimension = 4;
        sdku::SudokuPuzzle<puzzle_dimension> puzzle{"0340 4002 1002 0210"}; // Test puzzle (0s are empty cells)
        sdku::AlgorithmX solver{puzzle};

        // Solve
        std::println("Solving Puzzle:\n{}", puzzle.board());
        const auto solutions = solver.solve();

        // Result
        switch(solutions.size()) {
        case 0:
            std::println("No solutions found.\n");
            break;
        case 1:
            std::println("1 Solution Found!\n");
            std::println("{}", solutions[0].board());
            break;
        default:
            std::println("{} Solutions Found!\n", solutions.size());
            for (const auto& solution : solutions) {
                std::println("{}", solution.board());
            }
            break;
        }
    } catch (const std::exception& e) {
        std::println("An error occurred: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}