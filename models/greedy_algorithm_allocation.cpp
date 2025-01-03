#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a crop
struct Crop {
    int minFertilizer;  // Minimum fertilizer required
    int yield;          // Yield gained for the fertilizer
    int index;          // Index of the crop
};

// Comparator function to sort crops by yield per unit fertilizer in descending order
bool compareCrops(const Crop &a, const Crop &b) {
    double efficiencyA = static_cast<double>(a.yield) / a.minFertilizer;
    double efficiencyB = static_cast<double>(b.yield) / b.minFertilizer;
    return efficiencyA > efficiencyB;
}

// Function to allocate fertilizer using a greedy algorithm
void allocateFertilizer(vector<Crop> &crops, int totalFertilizer) {
    // Sort the crops based on yield efficiency
    sort(crops.begin(), crops.end(), compareCrops);

    vector<int> allocatedFertilizer(crops.size(), 0);
    int totalYield = 0;

    // Allocate fertilizer greedily
    for (const auto &crop : crops) {
        if (totalFertilizer >= crop.minFertilizer) {
            allocatedFertilizer[crop.index] = crop.minFertilizer;
            totalYield += crop.yield;
            totalFertilizer -= crop.minFertilizer;
        }
    }

    // Display allocation results
    cout << "\nFertilizer Allocation Results:\n";
    for (size_t i = 0; i < allocatedFertilizer.size(); ++i) {
        cout << "Crop " << i + 1 << ": Allocated Fertilizer = "
             << allocatedFertilizer[i] << "\n";
    }
    cout << "Total Yield: " << totalYield << "\n";
}

int main() {
    int numCrops, totalFertilizer;

    cout << "Enter the number of crops: ";
    cin >> numCrops;

    cout << "Enter the total available fertilizer: ";
    cin >> totalFertilizer;

    vector<Crop> crops(numCrops);

    // Input crop details
    for (int i = 0; i < numCrops; ++i) {
        cout << "Enter minimum fertilizer and yield for crop " << i + 1 << ": ";
        cin >> crops[i].minFertilizer >> crops[i].yield;
        crops[i].index = i;
    }

    // Allocate fertilizer and calculate yield
    allocateFertilizer(crops, totalFertilizer);

    return 0;
}
