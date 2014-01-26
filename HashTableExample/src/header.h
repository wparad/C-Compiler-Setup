/* 
 * File:   header.h
 * Author: Parad
 *
 * Created on January 23, 2014, 9:11 PM
 */

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */

// the initial capacity (number of buckets)
#define CAPACITY 100

typedef struct Node node;
struct Node {
  char* value;
  node* next; // next node in the list
};

typedef struct Hashtable hashtable;
struct Hashtable {
  node** list; // "buckets" of linked lists
  unsigned int length;
};

/* Function prototypes */
int hash(char *, unsigned long *);
int put(char *, hashtable *);
int get(char *, hashtable *);
int check_capacity(hashtable *);
void delete_hashtable(hashtable*);
hashtable* create_hashtable(unsigned int capacity);
int resize(hashtable *h, unsigned int capacity);

