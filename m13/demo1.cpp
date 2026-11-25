#include <iostream>
#include <string>

struct BuoyReading {
    std::string date;       // Replaces char date[12] — manages its own heap memory!
    double wave_height_ft;
    double wind_speed_kts;
};

// Pass by const reference: zero-copy like 'const BuoyReading *', but uses '.' instead of '->'
// and CANNOT be NULL!
void print_reading(const BuoyReading& r) {
    std::cout << "[" << r.date << "] Waves: " << r.wave_height_ft
              << " ft | Wind: " << r.wind_speed_kts << " kts\n";
}

// Pass by mutable reference: modifies caller's struct directly without '&' at call site
void calibrate_wave(BuoyReading& r, double offset) {
    r.wave_height_ft += offset;
}

int main() {
    BuoyReading rec{"2026-08-21", 8.4, 31.2};

    print_reading(rec);
    calibrate_wave(rec, -0.2);
    print_reading(rec);

    return 0;
}
