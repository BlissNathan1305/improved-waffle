#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits
#include <ios>    // Required for streamsize

// Function prototypes
void displayBoard(const std::vector<std::vector<char>>& board);
bool makeMove(std::vector<std::vector<char>>& board, int row, int col, char player);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
bool checkDraw(const std::vector<std::vector<char>>& board);
void gameLoop();

int main() {
    gameLoop();
    return 0;
}

// Function to display the Tic Tac Toe board
void displayBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "-------------" << std::endl;
    for (const auto& row : board) {
        std::cout << "| ";
        for (char cell : row) {
            std::cout << cell << " | ";
        }
        std::cout << std::endl << "-------------" << std::endl;
    }
}

// Function to handle a player's move
bool makeMove(std::vector<std::vector<char>>& board, int row, int col, char player) {
    // Check if the row and column are within the valid range (0, 1, 2)
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        std::cout << "Invalid move! Row and column must be between 1 and 3." << std::endl;
        return false;
    }

    // Check if the selected cell is empty
    if (board[row][col] != ' ') {
        std::cout << "Invalid move! That cell is already occupied." << std::endl;
        return false;
    }

    // Place the player's mark on the board
    board[row][col] = player;
    return true;
}

// Function to check if a player has won
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the game is a draw
bool checkDraw(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false; // If any cell is empty, it's not a draw yet
            }
        }
    }
    return true; // All cells are filled, and no winner means it's a draw
}

// Main game loop function
void gameLoop() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' ')); // Initialize empty board
    char currentPlayer = 'X';
    bool gameOver = false;

    std::cout << "Welcome to Tic Tac Toe!" << std::endl;

    while (!gameOver) {
        displayBoard(board);

        int row, col;
        std::cout << "Player " << currentPlayer << ", enter your move (row and column, 1-3): ";

        // Input validation loop
        while (!(std::cin >> row >> col)) {
            std::cout << "Invalid input. Please enter numbers for row and column (1-3): ";
            std::cin.clear(); // Clear the error flags
            // Ignore the rest of the invalid input in the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Adjust row and column to be 0-indexed for the vector
        row--;
        col--;

        if (makeMove(board, row, col, currentPlayer)) {
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                gameOver = true;
            } else if (checkDraw(board)) {
                displayBoard(board);
                std::cout << "It's a draw!" << std::endl;
                gameOver = true;
            } else {
                // Switch player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
         // Clear the input buffer after a successful read to prevent issues in the next iteration
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Game over." << std::endl;
}
