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
    
    for(count = 1; collection != NULL; collection = collection->next, count++);
    
    result->total_mammals = count;
    
    return result;
}

/*
 * Prints a list of pods and prints it out
 */

void print_pods(pod_list *pods) {
    //TODO: Do this later!!!
    int counter = 1;
    do {
        individual_list *mammals = pods->content->individuals;
        printf("Pod %d:\n",counter++);
        print_individuals(mammals);
    }while((pods = pods->next) != NULL);
}

/*
 * Takes in a linked list of individuals and removes any duplicates
 */

void tidy_individuals(pod_list *list) {
    pod_list *current;
    for (current = list; current != NULL; current = current->next) {
        pod_list *test;
        pod_list *last = current;
        for (test = current->next; test != NULL; test = test->next) {
            if (pod_contains(current, test)) {
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

int pod_contains(pod_list *main, pod_list *other) {
    individual_list *current = main->content->individuals;
    individual_list *test = other->content->individuals;
    while ((current = current->next) != NULL) {
        if (current->content == test->content) {
            return 1;
        }
    }
    return 0;
}

/*
 * Recursively find if mammal is close enough to any others to be in pod
 */

int is_close(individual *to_test, individual_list *list) {
    if (list->next == NULL) {
        if (great_circle(to_test->position, list->content->position) < 0.1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    if (great_circle(to_test->position, list->content->position) < 0.1) {
        return 1;
    }
    else {
        return is_close(to_test, list->next);
    }
}