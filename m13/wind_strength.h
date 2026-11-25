#ifndef WIND_STRENGTH_H
#define WIND_STRENGTH_H

// Returns: -1 (invalid), 0 (normal <25), 1 (gale 25-44.9), 2 (storm >=45)
int classify_wind(double speed_mph);

#endif
