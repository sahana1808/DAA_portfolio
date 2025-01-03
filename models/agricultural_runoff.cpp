#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// Constants for the problem
const int NUM_STAGES = 5;  // Number of crop growth stages
const int MAX_FERTILIZER = 100; // Maximum amount of fertilizer in units
const int MAX_SOIL_CAPACITY = 50; // Maximum soil nutrient saturation level
const double WEATHER_IMPACT[] = {1.0, 0.8, 1.2, 1.0, 0.9}; // Weather impact on fertilizer efficiency per stage

// Crop yield function based on fertilizer applied and weather impact
double calculateYield(int fertilizer, double weatherImpact) {
    return fertilizer * weatherImpact - 0.01 * fertilizer * fertilizer; // Hypothetical yield function
}

// Function to calculate runoff cost based on soil saturation
double calculateRunoffCost(int soilSaturation) {
    return soilSaturation > MAX_SOIL_CAPACITY ? (soilSaturation - MAX_SOIL_CAPACITY) * 2.0 : 0.0;
}

int main() {
    // DP table: dp[stage][soilSaturation]
    std::vector<std::vector<double>> dp(NUM_STAGES + 1, std::vector<double>(MAX_SOIL_CAPACITY + 1, 0.0));

    // Backtracking table to store optimal decisions
    std::vector<std::vector<int>> decision(NUM_STAGES, std::vector<int>(MAX_SOIL_CAPACITY + 1, 0));

    // Solve the DP table
    for (int stage = NUM_STAGES - 1; stage >= 0; --stage) {
        for (int soilSaturation = 0; soilSaturation <= MAX_SOIL_CAPACITY; ++soilSaturation) {
            double maxProfit = -std::numeric_limits<double>::infinity();
            int bestFertilizer = 0;

            for (int fertilizer = 0; fertilizer <= MAX_FERTILIZER; ++fertilizer) {
                int newSoilSaturation = soilSaturation + fertilizer;
                double yield = calculateYield(fertilizer, WEATHER_IMPACT[stage]);
                double runoffCost = calculateRunoffCost(newSoilSaturation);
                double profit = yield - runoffCost + dp[stage + 1][std::min(newSoilSaturation, MAX_SOIL_CAPACITY)];

                if (profit > maxProfit) {
                    maxProfit = profit;
                    bestFertilizer = fertilizer;
                }
            }

            dp[stage][soilSaturation] = maxProfit;
            decision[stage][soilSaturation] = bestFertilizer;
        }
    }

    // Output results
    std::cout << "Optimal Fertilization Schedule:" << std::endl;
    int soilSaturation = 0;
    for (int stage = 0; stage < NUM_STAGES; ++stage) {
        int fertilizer = decision[stage][soilSaturation];
        std::cout << "Stage " << stage + 1 << ": Apply " << fertilizer << " units of fertilizer" << std::endl;
        soilSaturation = std::min(soilSaturation + fertilizer, MAX_SOIL_CAPACITY);
    }

    std::cout << "Maximum Profit: " << dp[0][0] << std::endl;
    return 0;
}
