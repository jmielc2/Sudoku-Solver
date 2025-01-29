#include <print>

#include "AlgorithmX.hpp"

int main() {
    sdku::SudokuPuzzle puzzle{""};
    sdku::AlgorithmX<4> solver{puzzle};
    const std::vector<sdku::SudokuSolution> solutions = solver.solve();

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
    return EXIT_SUCCESS;
}