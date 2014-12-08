

#include "navigation.h"
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
 * Takes the ID code of an observer and a list of observers, and returns the
 * observer with that ID code.
 */

observer* find_obs(char *obs, observer_list *list) {
    observer_list *current = list;
    do {
        if (strcmp(obs, current->content->id) == 0) {
            return current->content;
        }
    } while ((current = current->next) != NULL);
    return NULL;
}

/*
 * Takes in a location and returns whether it is within the predefined
 * boundaries.
 */

int in_bounds(location loc) {
    return (loc.lat <= MAX_LAT && loc.lat >= MIN_LAT &&
            loc.lng <= MAX_LNG && loc.lng >= MIN_LNG);
}