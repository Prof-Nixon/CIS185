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
    FILE *fp = fopen("storms.bin", "rb");
    if (fp == NULL) {
        perror("Open failed");
        return 1;
    }

    // 1. Determine record count dynamically via fseek + ftell
    fseek(fp, 0, SEEK_END);
    long file_bytes = ftell(fp);
    long total_records = file_bytes / (long)sizeof(WeatherRecord);
    printf("Binary archive contains %ld records (%ld bytes).\n", total_records, file_bytes);

    // 2. Jump directly to Record #1 (Nov 1998) in O(1) time
    long target_index = 1;
    if (target_index < total_records) {
        fseek(fp, target_index * (long)sizeof(WeatherRecord), SEEK_SET);

        WeatherRecord rec;
        if (fread(&rec, sizeof(WeatherRecord), 1, fp) == 1) {
            printf("Direct Lookup [Index %ld]: %02d/%d | Peak Wind: %.1f mph\n",
                   target_index, rec.month, rec.year, rec.max_wind_mph);
        }
    }

    fclose(fp);
    fp = NULL;
    return 0;
}
