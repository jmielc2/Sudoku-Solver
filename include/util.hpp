#include "Sudoku.hpp"

#include <string>
#include <algorithm>

namespace sdku {
    inline std::string createEmptyBoard(const size_t D) {
        const size_t sqrt_d = std::sqrt(D);
        const size_t box_dim = sqrt_d + 1;
        const size_t x_dim = box_dim * sqrt_d;
        const size_t y_dim = x_dim - 1;
        const size_t length = y_dim * x_dim;
        std::string board(length, ' ');

        for (size_t y = 0; y < y_dim; y += 1) {
            char col = '|';
            if (y != 0 && (y + 1) % box_dim == 0) [[unlikely]] {
                std::fill(
                    board.begin() + y * x_dim,
                    board.begin() + y * x_dim + x_dim,
                    '-'
                );
                col = '+';
            }
            for (size_t x = box_dim - 1; x < x_dim; x += box_dim) {
                board[y * x_dim + x] = col;
            }
        }

        for (size_t y = 0; y < y_dim; y++) {
            board[y * x_dim + x_dim - 1] = '\n';
        }
        
        return board;
    }

    static inline void fillBoard(const size_t D, std::string& board, const PuzzleData_t& puzzle) {
        const size_t sqrt_d = std::sqrt(D);
        const size_t box_dim = sqrt_d + 1;
        const size_t x_dim = box_dim * sqrt_d;

        for (const auto& option : puzzle) {
            const Position_t& position = option.first;
            const size_t box_y = (position.second / sqrt_d);
            const size_t box_x = (position.first / sqrt_d);
            const size_t y = box_y + position.second;
            const size_t x = box_x + position.first;
            const size_t index = y * x_dim + x;
            board[index] = char(option.second + '0');
        }
    }

    template<class... T>
    inline std::string generateBoard(const size_t D, const T&... puzzle) {
        std::string board = createEmptyBoard(D);
        for (const auto& data : {puzzle...}) {
            fillBoard(D, board, data);
        }
        return board;
    }
}
