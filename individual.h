/* 
 * File:   individual.h
 * Author: chris
 *
 * Created on 17 November 2014, 20:47
 */

#ifndef INDIVIDUAL_H
#define	INDIVIDUAL_H

#include "navigation.h"

typedef struct {
    char species;
    unsigned int sighting_num;
    sighting_list *sightings;
    location position;
} individual;

typedef struct list_ind {
    individual *content;
    struct list_ind *next;
} individual_list;

/* 
 * Takes in two sightings, then returns the distance between the two of them.
 */

double get_distance (sighting *species1, sighting *species2);

/*
 * Takes in a linked list of sightings and, using the get_distance function,
 * determines which of those sightings are the same creature.
 * 
 * Returns a linked list of individual creatures.
 */

individual_list* find_individuals(sighting_list *sightings);

#endif	/* INDIVIDUAL_H */

/*
 * Takes in two sightings and returns if they are the same creature.
 */

int is_individual (sighting *sighting1, sighting *sighting2);

/*
 * Takes in a linked list of sightings and returns an individual
 */

individual* gen_individual(sighting_list *collection);

/*
 * Takes in a linked list of individuals and removes any duplicates
 */

void remove_duplicates(individual_list *list, individual_list *last);

/*
 * Prints out an organised list of individual creatures
 */

void print_individuals(individual_list *list);
