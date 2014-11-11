/* 
 * File:   sighting.h
 * Author: chris
 *
 * Created on 10 November 2014, 14:25
 */

#ifndef SIGHTING_H
#define	SIGHTING_H

#include <math.h>
#include "navigation.h"

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
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance (sighting *species1, sighting *species2);

/* 
 * Takes in a sighting linked list and a function pointer, and runs the
 * function on every member of the list.
 */

void sighting_walker(sighting_list *list,
        void (*function)(sighting_list *list));

void sighting_walker(sighting_list *in_list, sighting_list *out_list,
        void (*function)(sighting_list *in_list, sighting_list *out_list));

#endif	/* SIGHTING_H */

