#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 120
#define LINE_CAPACITY 128

typedef struct BuoyReading {
    char date[12];              // YYYY-MM-DD + '\0'
    double wave_height_ft;
    double dominant_period_sec;
    double water_temp_f;
    double wind_speed_kts;
} BuoyReading;

int main(int argc, char *argv[]) {
    const char *csv_path = "muskegon_buoy_summer_2026.csv";

    FILE *fp = fopen(csv_path, "r");
    if (fp == NULL) {
        perror("Unable to open Lake Michigan buoy dataset");
        return 1;
    }

    BuoyReading *readings = malloc(MAX_DAYS * sizeof(BuoyReading));
    if (readings == NULL) {
        fprintf(stderr, "Heap allocation failed.\n");
        fclose(fp);
        return 1;
    }

    char line[LINE_CAPACITY];

    // Step 1: Consume and discard the CSV header row
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "Error: CSV file is empty.\n");
        free(readings);
        fclose(fp);
        return 1;
    }

    // Step 2: Line-oriented parsing with fgets() + sscanf()
    int count = 0;
    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_DAYS) {
        // %10[^,] reads up to 10 non-comma characters safely into date[]
        int matched = sscanf(line, "%10[^,],%lf,%lf,%lf,%lf",
                             readings[count].date,
                             &readings[count].wave_height_ft,
                             &readings[count].dominant_period_sec,
                             &readings[count].water_temp_f,
                             &readings[count].wind_speed_kts);
        if (matched == 5) {
            count++;
        }
    }
    fclose(fp);

    if (count == 0) {
        fprintf(stderr, "No valid buoy observations parsed.\n");
        free(readings);
        return 1;
    }

    // Step 3: Analyze peak wave height and warmest water temperature
    int max_wave_idx = 0;
    int max_temp_idx = 0;
    double temp_sum = readings[0].water_temp_f;

    for (int i = 1; i < count; i++) {
        temp_sum += readings[i].water_temp_f;

        if (readings[i].wave_height_ft > readings[max_wave_idx].wave_height_ft) {
            max_wave_idx = i;
        }
        if (readings[i].water_temp_f > readings[max_temp_idx].water_temp_f) {
            max_temp_idx = i;
        }
    }

    printf("================================================================\n");
    printf("   LAKE MICHIGAN BUOY SUMMARY (MUSKEGON - SUMMER 2026)          \n");
    printf("================================================================\n");
    printf("Observations Loaded: %d days (from %s)\n", count, csv_path);
    printf("Mean Water Temp:     %.1f °F\n", temp_sum / count);
    printf("Peak Wave Event:     %.1f ft (Period: %.1f s, Wind: %.1f kts) on %s\n",
           readings[max_wave_idx].wave_height_ft,
           readings[max_wave_idx].dominant_period_sec,
           readings[max_wave_idx].wind_speed_kts,
           readings[max_wave_idx].date);
    printf("Warmest Water Day:   %.1f °F (Waves: %.1f ft) on %s\n",
           readings[max_temp_idx].water_temp_f,
           readings[max_temp_idx].wave_height_ft,
           readings[max_temp_idx].date);
    printf("================================================================\n");

    free(readings);
    readings = NULL;
    return 0;
}
