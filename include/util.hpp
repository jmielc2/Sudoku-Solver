#pragma once

#include "Sudoku.hpp"

#include <string>
#include <algorithm>
#include <fstream>
#include <variant>

namespace sdku {
    std::string createEmptyBoard(const size_t D) {
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

    inline void fillBoard(const size_t D, std::string& board, const PuzzleData_t& puzzle) {
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
            const Value_t value = option.second;
            if (value >= 10) [[unlikely]] {
                board[index] = char(option.second + 'A' - 10);
            } else {
                board[index] = char(option.second + '0');
            }
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

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::in | std::ios::ate);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        size_t length = file.tellg();
        std::string content(length, '\0');
        file.seekg(0);
        file.read(content.data(), length);
        return content;
    }

    std::string filterContent(const std::string& content) {
        std::string filtered_content;
        for (const auto c : content) {
            if (std::isdigit(c)) {
                filtered_content.push_back(c - '0');
            } else if (std::isupper(c) && c - 'A' + 10 <= 16) {
                filtered_content.push_back(c - 'A' + 10);
            } else if (!std::isspace(c)) {
                throw std::runtime_error("Invalid character in puzzle file: " + std::to_string(c));
            }
        }
        return filtered_content;
    }

    std::variant<SudokuPuzzle<4>, SudokuPuzzle<9>, SudokuPuzzle<16>> readPuzzleFile(const std::string& filename) {
        std::string filtered_content = filterContent(readFile(filename));
        switch (filtered_content.size()) {
        case 16:
            return SudokuPuzzle<4>(filtered_content);
        case 81:
            return SudokuPuzzle<9>(filtered_content);
        case 256:
            return SudokuPuzzle<16>(filtered_content);
        default:
            throw std::runtime_error("Invalid puzzle dimensions.");
        }
    }
}
