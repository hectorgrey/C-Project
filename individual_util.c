#include <stdlib.h>

#include "navigation.h"
#include "sighting.h"
#include "individual.h"

/* 
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance(sighting *sighting1, sighting *sighting2) {
    return great_circle(get_location(sighting1), get_location(sighting2));
}

/*
 * Takes in two sightings and returns if they are the same creature.
 */

int is_individual (sighting *sighting1, sighting *sighting2) {
    return (get_distance(sighting1, sighting2) < 0.02) &&
            sighting1->species == sighting2->species;
}

/*
 * Takes in a linked list of individuals and removes any duplicates
 */

void tidy_individuals(individual_list *list) {
    individual_list *current;
    for (current = list; current != NULL; current = current->next) {
        individual_list *test;
        individual_list *last = current;
        for (test = current->next; test != NULL; test = test->next) {
            if (ind_contains(current, test)) {
                last->next = test->next;
                free(test);
            }
            else {
                last = test;
            }
        }
    }
}

/*
 * Returns 1 if main contains other, or 0 if not.
 */

int ind_contains(individual_list *main, individual_list *other) {
    sighting_list *current = main->content->sightings;
    sighting_list *test = other->content->sightings;
    while ((current = current->next) != NULL) {
        if (current->content == test->content) {
            return 1;
        }
    }
    return 0;
}