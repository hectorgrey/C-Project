/* 
 * File:   sighting.c
 * Author: chris
 *
 * Created on 10 November 2014, 15:05
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "navigation.h"
#include "sighting.h"

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
    printf("Observations recorded at %02d/%02d/%4d at %02d:%02d:%02d.\n",
            day, month, year, hour, minute, second);
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
        current->content = malloc(sizeof(sighting));
        if ((current->content->obs = find_obs(obs, list)) == NULL) {
            fprintf(stderr, "Observer %s not found.\n", obs);
            continue;
        }
        current->content->species = species;
        current->content->bearing = bearing;
        current->content->distance = distance;
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
    printf("+===============+===============+=======================+\n");
    printf("| Observer\t| Species\t| Location\t\t|\n");
    printf("+---------------+---------------+-----------------------+\n");
    do {
        sighting *current = curr_sightings->content;
        location curr_location = get_location(current);
        if (!in_bounds(curr_location)) {
            continue;
        }
        printf("|%8s\t| %8s\t| (%f,%f)\t|\n",
                current->obs->id,
                current->species == 'P' ? "Porpoise" : "Dolphin",
                curr_location.lat, curr_location.lng);
    } while ((curr_sightings = curr_sightings->next) != NULL);
    printf("+===============+===============+=======================+\n");
    printf("\n");
}
