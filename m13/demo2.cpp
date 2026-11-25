#include <iostream>
#include <string>
#include <stdexcept>

class BuoyStation {
private:
    int id_;
    std::string location_;
    double water_temp_f_;

public:
    // Constructor: guarantees every object starts in a valid state
    BuoyStation(int id, const std::string& location, double temp_f)
        : id_(id), location_(location), water_temp_f_(temp_f) {
        if (temp_f < -40.0 || temp_f > 120.0) {
            throw std::invalid_argument("Water temperature out of physical range");
        }
    }

    // 'const' at the end promises this method will not mutate the object
    void print_status() const {
        std::cout << "Station " << id_ << " (" << location_
                  << "): " << water_temp_f_ << " F\n";
    }

    void update_temp(double new_temp_f) {
        if (new_temp_f >= -40.0 && new_temp_f <= 120.0) {
            water_temp_f_ = new_temp_f;
        }
    }
};

int main() {
    BuoyStation muskegon(45029, "Muskegon South Pierhead", 71.4);
    muskegon.print_status();

    muskegon.update_temp(72.8);
    muskegon.print_status();

    // When 'muskegon' hits '}', std::string's destructor runs automatically.
    // Zero malloc(), zero free(), zero leaks!
    return 0;
}
