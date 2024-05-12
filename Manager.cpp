//
// Created by Davide Teixeira on 12/05/2024.
//

#include "Manager.h"

double Manager::haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond){
    // Transformation into radians
    double rad_lat1= latitudeFirst * M_PI / 180;
    double rad_lon1 = latitudeFirst * M_PI / 180;
    double rad_lat2 = latitudeSecond * M_PI / 180;
    double rad_lon2 = longitudeSecond * M_PI / 180;

    // latitude and longitude variance
    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    // distance computation
    double aux = pow(sin(delta_lat / 2), 2) +
               pow(sin(delta_lon / 2), 2) * cos(rad_lat1) * cos(rad_lat2);

    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0-aux));

    double earthradius = 6371000.0;

    return earthradius * c;
}