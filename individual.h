/* 
 * File:   individual.h
 * Author: chris
 *
 * Created on 17 November 2014, 20:47
 */

#ifndef INDIVIDUAL_H
#define	INDIVIDUAL_H

#include "navigation.h"
#include "sighting.h"

typedef struct {
    
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

