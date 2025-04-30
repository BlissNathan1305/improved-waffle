#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <ios>    // Required for streamsize
#include <iomanip> // Required for std::setw

// Constants for the board size and empty cells
const int SIZE = 9;
const int SUBGRID_SIZE = 3;
const int EMPTY_CELL = 0;

// The game board (mutable) and the initial puzzle (for checking fixed cells)
int board[SIZE][SIZE];
int initialBoard[SIZE][SIZE]; // Stores the original puzzle to prevent overwriting initial numbers

// Predefined Sudoku puzzle (0 represents empty cells)
const int puzzle[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Function to display the Sudoku board
void displayBoard() {
    std::cout << "\n+-------+-------+-------+" << std::endl;
    for (int row = 0; row < SIZE; ++row) {
        std::cout << "| ";
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == EMPTY_CELL) {
                std::cout << "  "; // Print two spaces for empty cells
            } else {
                // Use different color/style for initial numbers (optional, requires libraries)
                // For simplicity, we'll just print the number
                std::cout << board[row][col] << " ";
            }
            if ((col + 1) % SUBGRID_SIZE == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((row + 1) % SUBGRID_SIZE == 0) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function to check if a number is valid in a specific cell according to Sudoku rules
// Does NOT check if the cell is empty or pre-filled, only checks conflicts with existing numbers
bool isValid(int row, int col, int num) {
    // Check row
    for (int c = 0; c < SIZE; ++c) {
        if (board[row][c] == num && c != col) {
            return false; // Number exists in the same row
        }
    }

    // Check column
    for (int r = 0; r < SIZE; ++r) {
        if (board[r][col] == num && r != row) {
            return false; // Number exists in the same column
        }
    }

    // Check 3x3 subgrid
    int startRow = (row / SUBGRID_SIZE) * SUBGRID_SIZE;
    int startCol = (col / SUBGRID_SIZE) * SUBGRID_SIZE;
    for (int r = startRow; r < startRow + SUBGRID_SIZE; ++r) {
        for (int c = startCol; c < startCol + SUBGRID_SIZE; ++c) {
            if (board[r][c] == num && r != row && c != col) {
                return false; // Number exists in the same 3x3 grid
            }
        }
    }

    return true; // Number is valid in this position
}

// Function to check if a player's intended move is valid
bool isMoveValid(int row, int col, int num) {
    // Check if row, col are within bounds (1-9 from user input)
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        std::cout << "Invalid move: Row or column out of bounds (must be 1-9)." << std::endl;
        return false;
    }

    // Check if the number is within the valid range (1-9) or 0 for clearing
    if (num < 0 || num > 9) {
        std::cout << "Invalid move: Number must be between 1 and 9 (or 0 to clear)." << std::endl;
        return false;
    }

    // Check if the cell is part of the initial puzzle
    if (initialBoard[row][col] != EMPTY_CELL && num != initialBoard[row][col] && num != EMPTY_CELL) {
         std::cout << "Invalid move: Cannot change the initial numbers." << std::endl;
         return false;
    }
     if (initialBoard[row][col] != EMPTY_CELL && num == EMPTY_CELL) {
         std::cout << "Invalid move: Cannot clear the initial numbers." << std::endl;
         return false;
    }


    // If the user is trying to place a number (not clear a cell)
    if (num != EMPTY_CELL) {
         // Check if the cell is already filled by the user
        if (board[row][col] != EMPTY_CELL && initialBoard[row][col] == EMPTY_CELL) {
            // Allow overwriting user's own numbers
             // std::cout << "Warning: You are overwriting a number you placed." << std::endl;
        }
        // Check if placing the number violates Sudoku rules with the current board state
        if (!isValid(row, col, num)) {
            std::cout << "Invalid move: Number " << num << " conflicts with existing numbers in row, column, or 3x3 grid." << std::endl;
            return false;
        }
    }


    // If num is 0, the move is valid if the cell was not part of the initial puzzle
     if (num == EMPTY_CELL && initialBoard[row][col] != EMPTY_CELL) {
          std::cout << "Invalid move: Cannot clear initial numbers." << std::endl;
          return false;
     }


    return true; // The move is valid
}


// Function to check if the board is completely filled
bool isBoardFull() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == EMPTY_CELL) {
                return false; // Found an empty cell
            }
        }
    }
    return true; // No empty cells found
}

// Function to check if the puzzle is solved correctly
bool isSolved() {
    if (!isBoardFull()) {
        return false; // Not solved if there are empty cells
    }

    // Check if every cell contains a valid number according to Sudoku rules
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (!isValid(row, col, board[row][col])) {
                return false; // Found an invalid number placement
            }
        }
    }

    return true; // Board is full and all numbers are valid
}

// Function to load the initial puzzle into the game board and fixed cells array
void loadPuzzle() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            board[row][col] = puzzle[row][col];
            initialBoard[row][col] = puzzle[row][col]; // Copy to keep track of original numbers
        }
    }
}

int main() {
    loadPuzzle(); // Load the predefined puzzle
    int row, col, num;
    bool gameWon = false;

    std::cout << "===== Welcome to Sudoku! =====" << std::endl;
    std::cout << "Fill the grid with numbers 1-9." << std::endl;
    std::cout << "Enter row, column, and number (1-9)." << std::endl;
    std::cout << "Enter 0 for number to clear a cell (only cells you filled)." << std::endl;
    std::cout << "Enter 0 for row to quit." << std::endl;

    while (!gameWon) {
        displayBoard();

        std::cout << "Enter move (row col num): ";

        // Input validation loop for row
        while (!(std::cin >> row)) {
             std::cout << "Invalid input for row. Please enter a number (1-9, or 0 to quit): ";
             std::cin.clear(); // Clear the error flags
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // Check for quit command
        if (row == 0) {
            std::cout << "Exiting game. Goodbye!" << std::endl;
            break; // Exit the game loop
        }

        // Input validation for col and num
        while (!(std::cin >> col >> num)) {
             std::cout << "Invalid input. Please enter column (1-9) and number (0-9): ";
             std::cin.clear(); // Clear the error flags
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
             // Re-prompt for row as well if the entire line was bad
             std::cout << "Enter move (row col num): " << row << " "; // Show the valid row they entered
        }


        // Adjust row and col to be 0-indexed for array access
        row--;
        col--;

        if (isMoveValid(row, col, num)) {
            // Make the move if valid
            board[row][col] = num;

            // Check if the puzzle is solved after the move
            if (isSolved()) {
                displayBoard();
                std::cout << "Congratulations! You solved the Sudoku puzzle!" << std::endl;
                gameWon = true; // End the game loop
            }
        }
        // If move was invalid, isMoveValid prints the error message. Loop continues.

         // Consume the rest of the line to prevent input issues in the next iteration
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } // End of while loop

    return 0;
}
