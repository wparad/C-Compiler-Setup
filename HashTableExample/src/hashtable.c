#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"

/*
 * For the given string referred to by the pointer "string",
 * calculate the hashcode and update the int "value".
 * 
 * Return 1 if successful, and 0 if an error occurred 
 * (e.g. if the string is null).
 */
int hash(char *string, unsigned long *value)
{
    
    if (string == NULL || value == NULL) return 0;
    long int sum = 0;
    unsigned int size = sizeof(string)/sizeof(string[0]);

    int i = 0;
    for (i = 0;  i < size-1; i++){
	int ascii_value = string[i];
        //sum = sum + ascii_value * pow(31,(size-1-i));
	sum += (ascii_value*31^(size-1-i));
    }
    (*value) = sum;
    return 1;
}



/*
 * Add the string to the hashtable in the appropriate "bucket".
 * 
 * Return 1 if successful, and 0 if an error occurred 
 * (e.g. if the string is null, if memory could not be allocated,
 * or if the string is already in the hashtable).
*/


int put(char *string, hashtable *h)
{
   if(string == NULL || h == NULL || get(string, h) == 1) return 0;
   int check = 0;
   unsigned long val = 0;
   check = hash(string, &val);
   if (check == 0) return 0;
   unsigned long location = val%CAPACITY;

	printf("%ld",location);

   //node* recur_node = NULL;
   node* recur_node = h->list[location];
   node* point = malloc(sizeof(node));
       if (point == NULL) {
           fprintf(stderr, "ERROR: create_node: malloc failed:");
           return 0;
       }
   point->next = NULL;
   point->value = string;
   if (recur_node == NULL) {
       h->list[location] = point;
   } else {
       while(1) {
           if (recur_node->next == NULL) break;
           recur_node = recur_node->next;
       }
       recur_node->next = point;
   }
   return 1;
}


/*
 * Determine whether the specified string is in the hashtable.
 * Return 1 if it is found, 0 if it is not (or if it is null).
*/ 
int get(char *string, hashtable *h)
{
    if(string == NULL || h == NULL) return 0;
    unsigned long val = 0;
    int check = 0;
    check = hash(string, &val);
    if (check == 0) return 0;
    
    unsigned long location = val%CAPACITY;

	printf("%ld",location);
    
    node* recur_node = h->list[location];
    int final = 0;
    while(recur_node != NULL){
        if (recur_node->value == NULL || strcmp(recur_node->value, string) == 0) final = 1;
        recur_node = recur_node->next;
    }
    return final;
}
