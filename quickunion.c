//
//  quickunion.c
//  union_find
//
//  Created by José Manuel Torres on 17/10/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#include "quickunion.h"


void initQU(int * id, int n) {
    int i;
    for (i = 0; i < n; i++) {
        id[i] = i;
    }
}

/** weighted improvement */
void initWQU(int * id, int * sz, int n) {
    int i;
    for (i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
}


int rootQU(int * id, int i) {
    while (i != id[i])
        i = id[i];
    return i;
}

void printDistances2rootQU(int * id, int i, int n) {
    printf("dist: ");
    for (i=0; i<n; i++) {
        printf("%d ", distance2rootQU(id, i));
    }
    printf("\n");
}


int distance2rootQU(int * id, int i) {
    int d=0;
    while (i != id[i])
    {
        i = id[i];
        d++;
    }
    return d;
}


int connectedQU(int * id, int p, int q) {
    return rootQU(id, p) == rootQU(id, q);
}

/**
 * Quick-Union com weighted improvement
 */
void unionWQU(int * id, int * sz, int n, int p, int q) {
    int i = rootQU(id, p);
    int j = rootQU(id, q);
    if  (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
    else                { id[j] = i; sz[i] += sz[j]; }
}

void unionQU(int * id, int n, int p, int q) {
    int i = rootQU(id, p);
    int j = rootQU(id, q);
    id[i] = j;
}

