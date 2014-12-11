#include <stdlib.h>
#include "navigation.h"
#include "sighting.h"
#include "individual.h"
#include "pod.h"

/*
 * Takes in a linked list of individuals and removes any duplicates
 */

void tidy_pods(pod_list *list) {
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
        if (current->content->position.lat == test->content->position.lat &&
                current->content->position.lng == test->content->position.lng) {
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
