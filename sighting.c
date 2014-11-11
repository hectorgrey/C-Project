/* 
 * File:   main.c
 * Author: chris
 *
 * Created on 10 November 2014, 15:05
 */

#include "sighting.h"

/*
 * Takes the sighting, then returns the location of the sighting.
 */

location get_location (sighting *species) {
    double bearing = to_radians(species->bearing);
    double distance = species->distance;
    double obs_lat = species->obs->loc.lat;
    double obs_lng = species->obs->loc.lng;
    double rad_lat = to_radians(obs_lat);
    double lat = obs_lat + (distance * cos(bearing)) / 60.0;
    double lng = obs_lng + (distance * sin(bearing) / cos(rad_lat)) / 60.0;
    location result = {lat, lng};
    return result;
}

/* 
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance(sighting *species1, sighting *species2) {
    return great_circle(get_location(species1), get_location(species2));
}

/* 
 * Takes in a sighting linked list and a function pointer, and runs the
 * function on every member of the list.
 */

void sighting_walker(sighting_list *list,
        void (*function)(sighting_list *list)) {
    function(list);
    sighting_walker(list->next, function);
}

void sighting_walker(sighting_list *in_list, sighting_list *out_list,
        void (*function)(sighting_list *in_list, sighting_list *out_list)) {
    function(in_list, out_list);
    sighting_walker(in_list->next, out_list->next, function);
}