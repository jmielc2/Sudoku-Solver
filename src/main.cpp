#include <print>
#include <string>
#include <chrono>

#include "AlgorithmX.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
    try {
        // Setup
        if (argc != 2) {
            std::println("Usage: ./sudoku <filename>");
            return EXIT_SUCCESS;
        }
        const std::string filename{argv[1]};
        const auto puzzle_variant = sdku::readPuzzleFile(filename);

        std::visit([](const auto& puzzle) {
            // Solve
            std::println("Solving Puzzle:\n{}", puzzle.board());
            sdku::AlgorithmX solver{puzzle};
            const auto start = std::chrono::high_resolution_clock::now();
            const auto solutions = solver.solve();
            const auto end = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::println("Solved in {}ms", duration.count());

            // Result
            switch(solutions.size()) {
            case 0:
                std::println("No solutions found.\n");
                break;
            case 1:
                std::println("1 solution found!\n");
                std::println("{}", solutions[0].board());
                break;
            default:
                std::println("{} solutions found!\n", solutions.size());
                for (const auto& solution : solutions) {
                    std::println("{}", solution.board());
                }
                break;
            }
        }, puzzle_variant);
    } catch (const std::exception& e) {
        std::println("{}\n", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}