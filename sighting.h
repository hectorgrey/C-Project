/* 
 * File:   sighting.h
 * Author: chris
 *
 * Created on 10 November 2014, 14:25
 */

#ifndef SIGHTING_H
#define	SIGHTING_H

#include <math.h>
#include <stdio.h>

#define to_radians(deg) ((deg) * M_PI) / 180
#define MAX_LNG -4.0
#define MIN_LNG -5.5
#define MAX_LAT 52.833
#define MIN_LAT 52.0

typedef struct {
    char *id;
    location loc;
} observer;

typedef struct list_obs {
    observer *content;
    struct list_obs *next;
} observer_list;

typedef struct {
    observer *obs;
    char species;
    double bearing;
    double distance;
} sighting;

typedef struct list_sight {
    sighting *content;
    struct list_sight *next;
} sighting_list;

/*
 * Takes the sighting, then returns the location of the sighting.
 */

location get_location (sighting *species);

/*
 * Takes the ID code of an observer and a list of observers, and returns the
 * observer with that ID code.
 */

observer* find_obs(char *obs, observer_list *list);

/*
 * Takes in a file containing a list of observers and returns a linked list
 * of observers.
 */

observer_list* read_observers(FILE *observers);

/*
 * Takes in a location and returns whether it is within the predefined
 * boundaries.
 */

int in_bounds(location loc);

/*
 * Takes in a file containing a list of sightings and returns a linked list
 * of sightings.
 */

sighting_list* read_sightings(FILE *sightings, observer_list *list);

/*
 * Takes in a list of sightings and prints out all sightings in tabulated form.
 */

void print_sightings(sighting_list *sightings);

#endif	/* SIGHTING_H */

