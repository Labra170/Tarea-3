//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 2018 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair {
     char * key;
     void * value;
} Pair;

Pair * createPair( char * key,  void * value);

long hash( char * key, long capacity);

int is_equal(void* key1, void* key2);

void enlarge(HashMap * map);

void insertMap(HashMap * map, char * key, void * value);

void enlarge(HashMap * map);

HashMap * createMap(long capacity);

void eraseMap(HashMap * map,  char * key);

Pair * searchMap(HashMap * map,  char * key);

Pair * firstMap(HashMap * map);

Pair * nextMap(HashMap * map);

#endif /* HashMap_h */
