#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#include "main.hpp"

const int DEPTH = 1;

int main(int, char**){
    std::cout << "Hello, from ConnectFour!\n" << std::endl;

    Board board;
    board.print_board();

    bool player = true;
    while (true) {
        char token = player ? 'o' : 'x';

        int column, row;

        if (!player) {
            int best_eval = -1;
            std::pair<int, int> best;
            for (auto const& move : board.get_legal_moves()) {
                int eval = board.evaluate_potential_position(move.first, move.second, token);
                if (eval > best_eval) {
                    best_eval = eval;
                    best = move;
                }
            }
            board.place_token(best.first, player);
            column = best.first;
            row = best.second;
            std::cout << "Computer played: " << "[" << best.first << ", " << best.second << "] " << "with evaluation of: " << best_eval << std::endl;
            board.print_board();
        } else {
            std::cout << "Enter the column you would like to place a token in!" << std::endl;
            std::cin >> column;
            row = board.get_highest_empty_space(column);
            if (!board.in_bounds(column, row)) {
                std::cout << "Move illegal, try again!" << std::endl;
                continue;
            }
            board.place_token(column, player);
            board.print_board();
            for (int dir = Direction::Vertical; dir <= Direction::R_Diagonal; ++dir) {
                Direction direction = static_cast<Direction>(dir);
                Connection connections = board.connections(column, row, token, direction);
                switch (direction) {
                    case Direction::Vertical:
                        std::cout << "VERT: " << connections.length() << std::endl;
                        break;
                    case Direction::Horizontal:
                        std::cout << "HOR: " << connections.length() << std::endl;
                        break;
                    case Direction::L_Diagonal:
                        std::cout << "LDiag: " << connections.length() << std::endl;
                        break;
                    case Direction::R_Diagonal:
                        std::cout << "RDiag: " << connections.length() << std::endl;
                        break;                                             
                }
                for (auto const& member : connections.members) {
                    std::cout << "[" << member.first << ", " << member.second << "]" << std::endl;
                }
            }
        }
        int evaluation = board.evaluate_actual_position(column, row);
        std::cout << "Evaluation: " << evaluation << std::endl;
        if (evaluation >= 1000000) {
            // Must be 4 or more length connection, therefore game is over.
            const char* winner = player ? "player" : "computer";
            std::cout << "Game over! Winner is: " << winner << std::endl;
            return 0;
        }
        player = !player;
    }
}