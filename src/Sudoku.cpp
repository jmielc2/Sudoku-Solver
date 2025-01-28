#include "Sudoku.hpp"

namespace sdku {
    
    std::ostream& operator<<(std::ostream& out, const SudokuSolution& solution) {
        return out << "Printing solution:\n" << solution.solution << "\n";
    }
}
