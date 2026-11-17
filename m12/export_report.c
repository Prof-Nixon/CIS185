#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "gale_warning.txt";

    // 1. Open file in write mode
    FILE *out_fp = fopen(filename, "w");
    if (out_fp == NULL) {
        perror("Failed to create report file");
        return 1;
    }

    // 2. Write formatted output identically to printf()
    fprintf(out_fp, "=================================================\n");
    fprintf(out_fp, "   MUSKEGON COAST GUARD METEOROLOGICAL BULLETIN  \n");
    fprintf(out_fp, "=================================================\n");
    fprintf(out_fp, "Station: KMKG | Peak Gust: %.1f mph | Temp: %.1f F\n", 67.5, 42.3);

    // 3. Always close to flush OS buffer to disk
    if (fclose(out_fp) != 0) {
        perror("Error closing file");
        return 1;
    }
    out_fp = NULL;

    printf("Successfully exported report to %s\n", filename);
    return 0;
}