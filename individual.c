/* 
 * File:   individual.c
 * Author: chris
 *
 * Created on 17 November 2014, 20:50
 */

#include "individual.h"

/* 
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance(sighting *species1, sighting *species2) {
    return great_circle(get_location(species1), get_location(species2));
}
