#include "distanceformula.h"

double toRadians(double angle)
{
    return angle * 4. * atan(1.) / 180.;
}

double distanceCalculation(double lat1, double lon1, double lat2, double lon2)
{
    double R = 3959, // mean radius in miles
           φ1 = toRadians(lat1),
           φ2 = toRadians(lat2),
           Δφ = toRadians(lat2-lat1),
           Δλ = toRadians(lon2-lon1),
           a = sin(Δφ/2) * sin(Δφ/2) + cos(φ1) * cos(φ2) * sin(Δλ/2) * sin(Δλ/2),
           c = 2.0 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}
