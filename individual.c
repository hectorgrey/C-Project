/* 
 * File:   individual.c
 * Author: chris
 *
 * Created on 17 November 2014, 20:50
 */

#include <stdlib.h>
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
    individual_list *current_ind = result;
    sighting_list *current_sight = sightings;
    
    do {
        sighting_list *i = current_sight->next;
        sighting_list *collection = malloc(sizeof(sighting_list));
        sighting *sighting1 = (collection->content = current_sight->content);
        do {
            sighting *sighting2 = i->content;
            if (is_individual(sighting1, sighting2)) {
                collection = (collection->next = malloc(sizeof(sighting_list)));
                collection->content = sighting2;
            }
        } while ((i = i->next) != NULL);
        current_ind->content = gen_individual(collection);
        free(collection);
    } while ((current_sight = current_sight->next) != NULL);
    
    return result;
}

/*
 * Takes in two sightings and returns if they are the same creature.
 */

int is_individual (sighting *sighting1, sighting *sighting2) {
    return get_distance(sighting1, sighting2) < 0.4;
}

/*
 * Takes in a linked list of sightings and returns an individual
 */

individual* gen_individual(sighting_list *collection) {
    
}