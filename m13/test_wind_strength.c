#include <stdio.h>
#include <assert.h>
#include "wind_strength.h"

void test_classify_wind_branches(void) {
    assert(classify_wind(-5.0) == -1);  // Invalid
    assert(classify_wind(12.0) == 0);   // Normal
    assert(classify_wind(30.0) == 1);   // Gale
    assert(classify_wind(50.0) == 2);   // Storm
    printf("[PASS] test_classify_wind_branches\n");
}

#ifdef TEST
int main(void) {
    test_classify_wind_branches();
    printf("All unit tests passed!\n");
    return 0;
}
#endif