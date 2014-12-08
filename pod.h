/* 
 * File:   pod.h
 * Author: chris
 *
 * Created on 17 November 2014, 20:48
 */

#ifndef POD_H
#define	POD_H

typedef struct {
    individual_list *individuals;
    int total_mammals;
} pod;

typedef struct list_pods {
    pod *content;
    struct list_pods *next;
} pod_list;

/* 
 * Takes a list of individuals, and returns a list of pods.
 */

pod_list* find_pods(individual_list *individuals);

/*
 * Takes a list of individuals and returns a pointer to a pod.
 */

pod* gen_pod(individual_list *collection);

/*
 * Prints a list of pods and prints it out
 */

void print_pods(pod_list *pods);

#endif	/* POD_H */

