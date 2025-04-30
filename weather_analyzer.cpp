#include <iostream> // For input/output operations (cin, cout)
#include <fstream>  // For file stream operations (ifstream)
#include <vector>   // To store the temperatures dynamically
#include <numeric>  // For std::accumulate (to sum the temperatures)
#include <algorithm> // For std::min_element and std::max_element

// Function to read temperatures from a file
bool readTemperaturesFromFile(const std::string& filename, std::vector<double>& temperatures) {
    std::ifstream inputFile(filename); // Open the file

    // Check if the file opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false; // Indicate failure
    }

    double temperature;
    // Read temperatures line by line until the end of the file
    while (inputFile >> temperature) {
        temperatures.push_back(temperature); // Add temperature to the vector
    }

    inputFile.close(); // Close the file
    return true; // Indicate success
}

// Function to calculate the average temperature
double calculateAverage(const std::vector<double>& temperatures) {
    if (temperatures.empty()) {
        return 0.0; // Avoid division by zero
    }
    // Use std::accumulate to sum all elements in the vector
    double sum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
    return sum / temperatures.size();
}

// Function to find the minimum temperature
double findMinimum(const std::vector<double>& temperatures) {
    if (temperatures.empty()) {
        // Return a very large number or handle as an error,
        // depending on desired behavior for empty data.
        // For this example, we'll assume non-empty data based on read success.
        // A robust application might throw an exception or return an optional.
        return 0.0; // Placeholder - should not be reached with successful read
    }
    // Use std::min_element to find the iterator to the minimum element
    return *std::min_element(temperatures.begin(), temperatures.end());
}

// Function to find the maximum temperature
double findMaximum(const std::vector<double>& temperatures) {
    if (temperatures.empty()) {
        // Similar to findMinimum, handle empty case appropriately.
        return 0.0; // Placeholder
    }
    // Use std::max_element to find the iterator to the maximum element
    return *std::max_element(temperatures.begin(), temperatures.end());
}

int main() {
    std::string filename;
    std::vector<double> temperatures;

    // Get the filename from the user
    std::cout << "Enter the name of the file containing temperature data: ";
    std::cin >> filename;

    // Read the temperatures from the file
    if (readTemperaturesFromFile(filename, temperatures)) {
        // Check if any data was actually read
        if (temperatures.empty()) {
            std::cout << "No temperature data found in the file." << std::endl;
        } else {
            // Perform calculations and display results
            double averageTemp = calculateAverage(temperatures);
            double minTemp = findMinimum(temperatures);
            double maxTemp = findMaximum(temperatures);

            std::cout << "\n--- Weather Analysis Results ---" << std::endl;
            std::cout << "Number of temperature readings: " << temperatures.size() << std::endl;
            std::cout << "Average Temperature: " << averageTemp << " degrees" << std::endl;
            std::cout << "Minimum Temperature: " << minTemp << " degrees" << std::endl;
            std::cout << "Maximum Temperature: " << maxTemp << " degrees" << std::endl;
            std::cout << "------------------------------" << std::endl;
        }
    }
    // If readTemperaturesFromFile returned false, an error message was already printed.

    return 0; // Indicate successful execution
}
