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

void remove_duplicates(individual_list *list, individual_list *last) {
    individual_list *current = list;
    if (list->next != NULL)
        remove_duplicates(list->next, list);
    if (last != NULL) {
        individual *record_a = current->content;
        individual *record_b = last->content;
        
        if (record_a->species == record_b->species &&
                great_circle(record_a->position, record_b->position) <= 0.02) {
            free(current);
            last->next = list->next;
        }
    }
}