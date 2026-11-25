#include <stdio.h>
#include <stdlib.h>

const char * messages[] = {
    "Error: Wind speed cannot be negative (%.1f mph).\n",
    "Normal Winds at %.1f mph\n",
    "Gale Force Winds at %.1f mph\n",
    "Storm Winds at %.1f mph\n",
};

int classify_wind(double speed_mph) {
    if (speed_mph < 0.0) 
    {
        return -1; // Invalid
    } 
    else if (speed_mph < 25.0) 
    {
        return 0;  // Normal
    } 
    else if (speed_mph < 45.0) 
    {
        return 1;  // Gale
    } 
    else 
    {
        return 2;  // Storm
    }
}

#ifndef TEST
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <wind_speed_mph>\n", argv[0]);
        return 1;
    }

    char *endptr = NULL;
    double speed = strtod(argv[1], &endptr);

    // Catch non-numeric input (e.g., "abc" or "25mph")
    if (endptr == argv[1] || *endptr != '\0') {
        printf("Error: '%s' is not a valid number.\n", argv[1]);
        return 1;
    }

    int category = classify_wind(speed);

    printf(messages[category + 1], speed);

    return 0;
}
#endif