#include <iostream>
#include "ttt.hpp"


// Constructor to initialize the game board and players
TicTacToe::TicTacToe() : board(3, std::vector<Player>(3, Player::None)), currentPlayer(Player::X), remainingMoves(9) {}


// Display the game board
void TicTacToe::show_board() const {
    
    std::cout << "  -----------\n";
    for (const auto& row : board) {
        std::cout << " | ";
        for (const auto& cell : row) {
            if (cell == Player::X) std::cout << 'X';
            else if (cell == Player::O) std::cout << 'O';
            else std::cout << ' ';
            std::cout << " | ";
        }
        std::cout << "\n  -----------\n";
    }
}


// Handle player input and validate it
std::tuple<int, int> TicTacToe::take_player_input() const {
    int row_num, col_num;
    bool validInput = false;

    while (!validInput) {
        std::cout << "\n ***** Player " << (currentPlayer == Player::X ? "X" : "O") << "'s Turn *****\n";
        std::cout << "Please Choose Row Number (1-3): ";
        std::cin >> row_num;
        std::cout << "Please Choose Column Number (1-3): ";
        std::cin >> col_num;

        if (row_num >= 1 && row_num <= 3 && col_num >= 1 && col_num <= 3 && board[row_num - 1][col_num - 1] == Player::None) {
            validInput = true;
        } else {
            std::cout << "Invalid input or slot already occupied. Please try again.\n";
        }
    }
    return {row_num - 1, col_num - 1};
}


// Check if the current player is a winner
bool TicTacToe::check_winner(int row_idx, int col_idx) const {
    Player player = currentPlayer;

    // Check row, column, and diagonals
    bool rowWin = board[row_idx][0] == player && board[row_idx][1] == player && board[row_idx][2] == player;
    bool colWin = board[0][col_idx] == player && board[1][col_idx] == player && board[2][col_idx] == player;
    bool diagWin1 = board[0][0] == player && board[1][1] == player && board[2][2] == player;
    bool diagWin2 = board[0][2] == player && board[1][1] == player && board[2][0] == player;

    return rowWin || colWin || diagWin1 || diagWin2;
}


// The main game loop
void TicTacToe::play() {
    while (remainingMoves > 0) {
        // Display the board
        show_board();

        int row_idx, col_idx;

        // Take player input
        std::tie(row_idx, col_idx) = take_player_input();

        // Update the board and remaining moves
        board[row_idx][col_idx] = currentPlayer;
        remainingMoves--;

        // Check if the current player is a winner
        if (check_winner(row_idx, col_idx)) {
            show_board();
            std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << " wins!\n";
            return;
        }

        // Switch player
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    show_board();
    std::cout << "It's a tie!\n";
}