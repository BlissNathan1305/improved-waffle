#include <iostream>

int main() {
    int numTerms;

    // Get the number of terms from the user
    std::cout << "Enter the number of Fibonacci terms to output: ";
    std::cin >> numTerms;

    // --- Input Validation ---
    if (numTerms < 0) {
        std::cerr << "Error: Please enter a non-negative number of terms." << std::endl;
        return 1; // Indicate an error
    }

    std::cout << "Fibonacci Sequence (first " << numTerms << " terms):" << std::endl;

    // --- Generate and Output Sequence ---

    // Handle the first two terms separately as the base cases
    if (numTerms >= 1) {
        std::cout << 0; // First term
    }

    if (numTerms >= 2) {
        std::cout << ", " << 1; // Second term
    }

    // If we need more than 2 terms, calculate and print the rest
    if (numTerms > 2) {
        long long term1 = 0; // Use long long to accommodate larger numbers
        long long term2 = 1;
        long long nextTerm;

        // Loop to calculate the remaining terms
        for (int i = 3; i <= numTerms; ++i) {
            nextTerm = term1 + term2; // Calculate the next term
            std::cout << ", " << nextTerm; // Print the next term

            // Update term1 and term2 for the next iteration
            term1 = term2;
            term2 = nextTerm;
        }
    }

    std::cout << std::endl; // Newline at the end

    return 0; // Indicate successful execution
}
