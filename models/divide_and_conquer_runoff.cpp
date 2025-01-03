#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Function to calculate runoff for a single grid
double calculateRunoff(double rainfall, double soilAbsorption, double saturationLimit) {
    double excessWater = std::max(0.0, rainfall - soilAbsorption);
    return std::min(excessWater, saturationLimit);
}

// Function to simulate runoff using Divide and Conquer
double simulateRunoff(const std::vector<std::vector<double>> &field, int startRow, int endRow, int startCol, int endCol) {
    // Base case: Single grid
    if (startRow == endRow && startCol == endCol) {
        double rainfall = field[startRow][startCol];  // Rainfall value for this grid
        double soilAbsorption = 10.0;                // Hypothetical soil absorption capacity
        double saturationLimit = 20.0;               // Hypothetical saturation limit
        return calculateRunoff(rainfall, soilAbsorption, saturationLimit);
    }

    // Divide: Split the field into 4 subfields
    int midRow = (startRow + endRow) / 2;
    int midCol = (startCol + endCol) / 2;

    double topLeft = simulateRunoff(field, startRow, midRow, startCol, midCol);
    double topRight = simulateRunoff(field, startRow, midRow, midCol + 1, endCol);
    double bottomLeft = simulateRunoff(field, midRow + 1, endRow, startCol, midCol);
    double bottomRight = simulateRunoff(field, midRow + 1, endRow, midCol + 1, endCol);

    // Conquer: Combine results from subfields
    return topLeft + topRight + bottomLeft + bottomRight;
}

int main() {
    // Hypothetical field with rainfall data (in mm)
    std::vector<std::vector<double>> field = {
        {30.0, 40.0, 35.0, 25.0},
        {20.0, 15.0, 50.0, 45.0},
        {10.0, 25.0, 30.0, 20.0},
        {35.0, 40.0, 20.0, 15.0}
    };

    int rows = field.size();
    int cols = field[0].size();

    // Simulate runoff for the entire field
    double totalRunoff = simulateRunoff(field, 0, rows - 1, 0, cols - 1);

    // Output the result
    std::cout << "Total Runoff for the Field: " << totalRunoff << " units" << std::endl;

    return 0;
}
