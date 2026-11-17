#include <stdio.h>
#include <stdlib.h>

typedef struct WeatherRecord {
    int year;
    int month;
    double max_wind_mph;
    double avg_temp_f;
    double total_precip_in;
} WeatherRecord;

int main(void) {
    WeatherRecord samples[3] = {
        {1913, 11, 68.2, 38.4, 3.45},
        {1998, 11, 67.5, 42.3, 2.38},
        {1940, 11, 66.8, 36.1, 3.12}
    };

    // 1. Serialize entire array to binary file in one call
    FILE *wb = fopen("storms.bin", "wb");
    if (wb == NULL) {
        perror("Binary write open failed");
        return 1;
    }
    size_t written = fwrite(samples, sizeof(WeatherRecord), 3, wb);
    fclose(wb);
    printf("Wrote %zu binary records (%zu bytes total).\n",
           written, written * sizeof(WeatherRecord));

    // 2. Deserialize back into a fresh heap buffer
    WeatherRecord *loaded = malloc(3 * sizeof(WeatherRecord));
    if (loaded == NULL) return 1;

    FILE *rb = fopen("storms.bin", "rb");
    if (rb == NULL) {
        perror("Binary read open failed");
        free(loaded);
        return 1;
    }
    size_t read_count = fread(loaded, sizeof(WeatherRecord), 3, rb);
    fclose(rb);

    printf("\n--- Reloaded Binary Records (%zu) ---\n", read_count);
    for (size_t i = 0; i < read_count; i++) {
        printf("[%zu] %02d/%d | Wind: %.1f mph | Temp: %.1f F\n",
               i, loaded[i].month, loaded[i].year,
               loaded[i].max_wind_mph, loaded[i].avg_temp_f);
    }

    free(loaded);
    loaded = NULL;
    return 0;
}
