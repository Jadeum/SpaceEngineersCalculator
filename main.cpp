#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

struct Material {
    std::string type;
    int cost; // Change the cost to int
};

std::vector<Material> readCSV(const std::string &filename) {
    std::vector<Material> materials;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return materials;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string materialType;
        int materialCost; // Change the cost to int

        if (std::getline(iss, materialType, ',') && iss >> materialCost) {
            materials.push_back({materialType, materialCost});
        } else {
            std::cerr << "Error: Invalid line in CSV file: " << line << std::endl;
        }
    }

    file.close();
    return materials;
}

std::map<std::string, int> calculateTotalCost(const std::vector<Material> &materials) {
    std::map<std::string, int> totalCosts;

    for (const auto &material : materials) {
        totalCosts[material.type] += material.cost;
    }

    return totalCosts;
}

int main() {
    // Read and parse "components.csv"
    std::vector<Material> components = readCSV("/home/augie/CLionProjects/SpaceEngineersEconomyCalculator/csv-files/components.csv");

    // Read and parse "ingots.csv"
    std::vector<Material> ingots = readCSV("/home/augie/CLionProjects/SpaceEngineersEconomyCalculator/csv-files/ingots.csv");

    // Read and parse "ammunition.csv"
    std::vector<Material> ammunition = readCSV("/home/augie/CLionProjects/SpaceEngineersEconomyCalculator/csv-files/ammunition.csv");


    // Calculate total costs for each type of material
    std::map<std::string, int> totalComponentCosts = calculateTotalCost(components);
    std::map<std::string, int> totalIngotCosts = calculateTotalCost(ingots);
    std::map<std::string, int> totalAmmunitionCosts = calculateTotalCost(ammunition);

    // Accept user input for the amount of gold ingots in kg
    double goldIngotKg;
    std::cout << "Enter the amount of gold ingots in kg: ";
    std::cin >> goldIngotKg;

    // Calculate and print the results for all materials
    std::cout << "Results:" << std::endl;
    for (const auto &entry : totalIngotCosts) {
        const std::string &type = entry.first;
        int cost = entry.second;

        if (cost > 0) {
            int numberOfItems = static_cast<int>(goldIngotKg * 6200 / cost);
            std::cout << "Type: " << type << ", Worth: " << numberOfItems << " " << type << std::endl;
        }
    }

    for (const auto &entry : totalComponentCosts) {
        const std::string &type = entry.first;
        int cost = entry.second;

        if (cost > 0) {
            int numberOfItems = static_cast<int>(goldIngotKg * 6200 / cost);
            std::cout << "Type: " << type << ", Worth: " << numberOfItems << " " << type << std::endl;
        }
    }

    for (const auto &entry : totalAmmunitionCosts) {
        const std::string &type = entry.first;
        int cost = entry.second;

        if (cost > 0) {
            int numberOfItems = static_cast<int>(goldIngotKg * 6200 / cost);
            std::cout << "Type: " << type << ", Worth: " << numberOfItems << " " << type << std::endl;
        }
    }

    return 0;
}
