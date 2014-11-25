/* 
 * File:   main.c
 * Author: chris
 *
 * Created on 10 November 2014, 14:05
 */

#include <stdio.h>
#include <stdlib.h>

#include "individual.h"

/*
 * Takes no arguments.
 */

int main(int argc, char** argv) {
    FILE *s_file;
    FILE *o_file;
    char *s_path = malloc(21);
    char *o_path = malloc(21);
    sighting_list *sightings;
    observer_list *observers;
    individual_list *individuals;
    
    // File reading and data parsing
    
    printf("Please enter the file name you wish to load the observers from: ");
    scanf("%s", o_path);
    printf("Please enter the file name you wish to load the sightings from: ");
    scanf(" %s", s_path);
    o_file = fopen(o_path, "r");
    s_file = fopen(s_path, "r");
    if (o_file == NULL) {
        fprintf(stderr, "Error opening file %s.  Quitting.\n", o_path);
        return (EXIT_FAILURE);
    }
    if (s_file == NULL) {
        fprintf(stderr, "Error opening file %s.  Quitting.\n", s_path);
        fclose(o_file);
        return (EXIT_FAILURE);
    }
    
    observers = read_observers(o_file);
    sightings = read_sightings(s_file, observers);
    fclose(o_file);
    fclose(s_file);
    
    // Function 1
    
    printf("All sightings within bounds:\n");
    
    print_sightings(sightings);
    
    // Function 2
    
    printf("All individuals within bounds:\n");
    
    individuals = find_individuals(sightings);
    
    print_individuals(individuals);
    
    // Function 3
    
    return (EXIT_SUCCESS);
}