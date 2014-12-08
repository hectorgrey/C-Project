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

#endif	/* POD_H */

