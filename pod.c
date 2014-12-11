/* 
 * File:   pod.c
 * Author: chris
 *
 * Created on 17 November 2014, 20:50
 */

#include<stdio.h>
#include<stdlib.h>

#include "navigation.h"
#include "sighting.h"
#include "individual.h"
#include "pod.h"

/* 
 * Takes a list of individuals, and returns a list of pods.
 */

pod_list* find_pods(individual_list *individuals) {
    pod_list *result = malloc(sizeof(pod_list));
    pod_list *current = result;
    pod_list *tail = current;
    
    do {
        if (in_bounds(individuals->content->position)) {
            individual_list *coll_root = malloc(sizeof(individual_list));
            individual_list *coll_curr = coll_root;
            individual_list *remainder = individuals->next;
            coll_curr->content = individuals->content;
            coll_curr->next = NULL;
            while (remainder != NULL) {
                if (in_bounds(remainder->content->position) &&
                        is_close(remainder->content, coll_root)) {
                    coll_curr = coll_curr->next = malloc(sizeof(individual_list));
                    coll_curr->content = remainder->content;
                    coll_curr->next = NULL;
                }
                remainder = remainder->next;
            }
            current->content = gen_pod(coll_root);
            tail = current;
            current = current->next = malloc(sizeof(pod_list));
        }
    } while((individuals = individuals->next) != NULL);
    
    tail->next = NULL;
    free(current);
    
    tidy_pods(result);
    
    return result;
}

/*
 * Takes a list of individuals and returns a pointer to a pod.
 */

pod* gen_pod(individual_list *collection) {
    pod *result = malloc(sizeof(pod));
    int count;
    
    result->individuals = collection;
    
    for(count = 0; collection != NULL; collection = collection->next, count++);
    
    result->total_mammals = count;
    
    return result;
}

/*
 * Prints a list of pods and prints it out
 */

void print_pods(pod_list *pods) {
    int counter = 1;
    printf("+==================================================+\n");
    do {
        individual_list *mammals;
        printf("| Pod %d:\t\t\t\t\t   |\n",counter++);
        printf("+-----------------------+---------------+----------+\n");
        printf("| Location\t\t| Sightings\t|  Species |\n");
        printf("+-----------------------+---------------+----------+\n");
        for(mammals = pods->content->individuals;
                mammals != NULL;
                mammals = mammals->next) {
            individual *record = mammals->content;
            printf("|(%f, %f)\t|%8d\t| %8s |\n",
                    record->position.lat, record->position.lng,
                    record->sighting_num,
                    record->species == 'P' ? "Porpoise" : "Dolphin");
            printf("+-----------------------+---------------+----------+\n");
        }
        printf("| %d animals in pod.\t\t\t\t   |\n",
                pods->content->total_mammals);
        printf("+==================================================+\n");
    }while((pods = pods->next) != NULL);
}