/* 
 * File:   individual.c
 * Author: chris
 *
 * Created on 17 November 2014, 20:50
 */

#include <stdlib.h>
#include <stdio.h>
#include "individual.h"

/* 
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance(sighting *sighting1, sighting *sighting2) {
    return great_circle(get_location(sighting1), get_location(sighting2));
}

/*
 * Takes in a linked list of sightings and, using the get_distance function,
 * determines which of those sightings are the same creature.
 * 
 * Returns a linked list of individual creatures.
 */

individual_list* find_individuals(sighting_list *sightings){
    individual_list *result = malloc(sizeof(individual_list));
    result->next = NULL;
    individual_list *current_ind = result;
    individual_list *last_ind = result;
    sighting_list *current_sight = sightings;
    sighting_list *last_sight = sightings;
    
    do {
        sighting_list *i;
        sighting_list *collection = malloc(sizeof(sighting_list));
        sighting_list *curr_entry = collection;
        collection->next = NULL;
        sighting *sighting1 = (collection->content = current_sight->content);
        for(i = current_sight->next; i != NULL; i = i->next) {
            sighting *sighting2 = i->content;
            if (is_individual(sighting1, sighting2)) {
                curr_entry = (curr_entry->next = malloc(sizeof(sighting_list)));
                curr_entry->content = sighting2;
                curr_entry->next = NULL;
            }
            last_sight = i;
        }
        current_ind->content = gen_individual(collection);
        last_ind = current_ind;
        current_ind = (current_ind->next = malloc(sizeof(individual_list)));
        free(collection);
        last_sight = current_sight;
    } while ((current_sight = current_sight->next) != NULL);
    last_ind->next = NULL;
    free(current_ind);
    remove_duplicates(result);
    
    return result;
}

/*
 * Takes in two sightings and returns if they are the same creature.
 */

int is_individual (sighting *sighting1, sighting *sighting2) {
    return (get_distance(sighting1, sighting2) < 0.02) &&
            sighting1->species == sighting2->species;
}

/*
 * Takes in a linked list of sightings and returns an individual
 */

individual* gen_individual(sighting_list *collection) {
    sighting_list *curr_entry = collection;
    unsigned int counter = 0;
    char species = collection->content->species;
    location total;
    total.lat = 0;
    total.lng = 0;
    individual *result = malloc(sizeof(individual));
    do {
        location current = get_location(curr_entry->content);
        total.lat += current.lat;
        total.lng += current.lng;
        counter++;
    } while((curr_entry = curr_entry->next) != NULL);
    total.lat /= counter;
    total.lng /= counter;
    result->sightings = counter;
    result->position = total;
    result->species = species;
    return result;
}

/*
 * Takes in a linked list of individuals and removes any duplicates
 */

void remove_duplicates(individual_list *list) {
    individual_list *current;
    for (current = list; current->next != NULL; current = current->next) {
        individual_list *last = current;
        individual_list *check;
        for (check = current->next; check != NULL; check = check->next) {
            individual *record_a = current->content;
            individual *record_b = check->content;
            if (record_a->species == record_b->species &&
                    record_a->position.lat == record_b->position.lat &&
                    record_a->position.lng == record_b->position.lng) {
                last->next = check->next;
                free(check);
            }
            last = check;
        }
    }
}

/*
 * Prints out an organised list of individual creatures
 */

void print_individuals(individual_list *list){
    individual_list *current = list;
    printf("Location\t\tSightings\tSpecies\n\n");
    do {
        individual *record = current->content;
        if (in_bounds(record->position)) {
            printf("(%f, %f)\t%8d\t%s\n",
                    record->position.lat, record->position.lng,
                    record->sightings,
                    record->species == 'P' ? "Porpoise" : "Dolphin");
        }
    } while ((current = current->next) != NULL);
    printf("\n");
}