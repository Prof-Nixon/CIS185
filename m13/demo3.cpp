#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct BuoyReading {
    std::string date;
    double wave_height_ft;
    double water_temp_f;
};

int main() {
    std::ifstream file("muskegon_buoy_summer_2026.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file.\n";
        return 1;
    }

    std::vector<BuoyReading> records;
    std::string line;

    std::getline(file, line); // Skip CSV header row

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, wave_str, period_str, temp_str;

        if (std::getline(ss, date, ',') &&
            std::getline(ss, wave_str, ',') &&
            std::getline(ss, period_str, ',') &&
            std::getline(ss, temp_str, ',')) {
            records.push_back({date, std::stod(wave_str), std::stod(temp_str)});
        }
    }
    // 'file' automatically closes here via RAII!

    // Type-safe sort from highest wave to lowest (replaces qsort + void*)
    std::sort(records.begin(), records.end(), [](const BuoyReading& a, const BuoyReading& b) {
        return a.wave_height_ft > b.wave_height_ft;
    });

    std::cout << "Loaded " << records.size() << " records.\n";
    if (!records.empty()) {
        std::cout << "Peak Wave: " << records[0].wave_height_ft
                  << " ft on " << records[0].date << "\n";
    }

    return 0; // 'records' vector automatically frees all heap memory here!
}
