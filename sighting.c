/* 
 * File:   main.c
 * Author: chris
 *
 * Created on 10 November 2014, 15:05
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
 * Takes in a sighting linked list and a function pointer, and runs the
 * function on every member of the list.
 */

void sighting_walker(sighting_list *list,
        void (*function)(sighting_list *list)) {
    function(list);
    sighting_walker(list->next, function);
}

/*
 * Takes in an observer linked list and a function pointer, and runs the
 * function on every member of the list.
 */

void observer_walker(observer_list *list,
        void (*function)(observer_list *list)) {
    function(list);
    observer_walker(list->next, function);
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
 * Takes in a file containing a list of observers and returns a linked list
 * of observers.
 */

observer_list* read_observers (FILE *observers) {
    observer_list *result = malloc(sizeof(observer_list));
    observer_list *last = NULL;
    observer_list *current = result;
    double lat, lng;
    int day, month, year, hour, minute, second;
    char *id = malloc(5);
    fscanf(observers, " %d %d %d %d %d %d", &day, &month, &year,
            &hour, &minute, &second);
    printf("Observations recorded at %c%d/%c%d/%4d at %c%d:%c%d:%c%d.\n",
            day < 10 ? '0' : '\0', day, 
            month < 10 ? '0' : '\0', month, year,
            hour < 10 ? '0' : '\0', hour,
            minute < 10 ? '0' : '\0', minute,
            second < 10 ? '0' : '\0', second);
    while(fscanf(observers, " %s %lf %lf", id, &lat, &lng)
            != EOF) {
        current->content = malloc(sizeof(observer));
        current->content->id = malloc(5);
        strcpy(current->content->id, id);
        current->content->loc.lat = lat;
        current->content->loc.lng = lng;
        last = current;
        current = current->next = malloc(sizeof(observer_list));
    }
    last->next = NULL;
    free(current);
    return result;
}

/*
 * Takes in a location and returns whether it is within the predefined
 * boundaries.
 */

int in_bounds(location loc) {
    return (loc.lat <= MAX_LAT && loc.lat >= MIN_LAT &&
            loc.lng <= MAX_LNG && loc.lng >= MIN_LNG);
}

/*
 * Takes in a file containing a list of sightings and returns a linked list
 * of sightings.
 */

sighting_list* read_sightings (FILE *sightings, observer_list *list) {
    sighting_list *result = malloc(sizeof(sighting_list));
    sighting_list *last = NULL;
    sighting_list *current = result;
    char *obs = malloc(5);
    char species;
    double bearing, distance;
    while(fscanf(sightings, " %s %c %lf %lf",
            obs, &species, &bearing, &distance) != EOF) {
        location loc;
        current->content = malloc(sizeof(sighting));
        if ((current->content->obs = find_obs(obs, list)) == NULL) {
            fprintf(stderr, "Observer %s not found.\n", obs);
            continue;
        }
        current->content->species = species;
        current->content->bearing = bearing;
        current->content->distance = distance;
        loc = get_location(current->content);
        last = current;
        current = current->next = malloc(sizeof(sighting_list));
    }
    last->next = NULL;
    free(current);
    return result;
}

/*
 * Takes in a list of sightings and prints out all sightings in tabulated form.
 */

void print_sightings(sighting_list *sightings) {
    sighting_list *curr_sightings = sightings;
    printf("Observer\tSpecies\t\tLocation\n\n");
    do {
        sighting *current = curr_sightings->content;
        location curr_location = get_location(current);
        if (!in_bounds(curr_location)) {
            continue;
        }
        printf("%8s\t%8s\t(%f,%f)\n",
                current->obs->id,
                current->species == 'P' ? "Porpoise" : "Dolphin",
                curr_location.lat, curr_location.lng);
    } while ((curr_sightings = curr_sightings->next) != NULL);
    printf("\n");
}
