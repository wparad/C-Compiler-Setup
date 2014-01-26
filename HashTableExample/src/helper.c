

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

/*
 * For the given string referred to by the pointer "string",
 * calculate the hashcode and update the int "value".
 * 
 * Return 1 if successful, and 0 if an error occurred 
 * (e.g. if the string is null).
 */
int hash(char *string, unsigned long *value)							//to determine to which bucket in a hashtable a string belongs
{
    if (string == NULL || value == NULL) return 0;						//check there is something worth looking at return 0 if error
    long int sum = 0;													//int for a hash value
    int size = strlen(string);                                          //get the size of the string
    int i = 0;
    for (i = 0;  i < size; i++){										//for each character of the string
        int ascii_value = string[i];									//get the ascii value of the character
        sum = sum + ascii_value*i;                                      //formula for hash value
        //sum += ascii_value;
    }
    (*value) = sum;           									//mod it so that it fits in our buckets
    //(*value) = 1;
    return 1;															//return 1 if successful
}



/*
 * Add the string to the hashtable in the appropriate "bucket".
 * 
 * Return 1 if successful, and 0 if an error occurred 
 * (e.g. if the string is null, if memory could not be allocated,
 * or if the string is already in the hashtable).
*/


int put(char *string, hashtable *h)										//for putting a word into the hashtable
{
   if(string == NULL ||strlen(string) == 0 || h == NULL || get(string, h) == 1) return 0;		//check that there is a word and a hashtable and that the word is not already in the hashtable
   unsigned long val = 0;												//where the hash value will be stored

   if (hash(string, &val) == 0) return 0;										//if there is a hash error, return 0 for error
   val %= h->length;
   if (!(val >=0 && val <=(h->length-1))) return 0;						//a second check that val is within the correct range -- this should be able to be deleted

   node* point = malloc(sizeof(node));									//create node in the heap
   if (point == NULL) {												//if there was an error allocating memory
	   fprintf(stderr, "ERROR: create_node: malloc failed:");
	   return 0;													//return error 0
   }

    char* n_string = malloc(strlen(string)*sizeof(char)+1);							//create a string in memory
    if (n_string == NULL){												//if there was an error allocating memory
        printf("Error in malloc");
        free(point);
        return 0;														//return error 0
    }
   strcpy(n_string,string);       										//copy string on stack to string in heap 
           
   point->value = n_string;
   point->next = NULL;

   node* recur_node = h->list[val];
   if (h->list[val] == NULL) { //if the head pointer in the heap is null
       h->list[val] = point; //set the head pointer to point to point (as the node of this bucket's linked list)
   }
   else { //if there already exists a linked list
	   for(recur_node = h->list[val]; recur_node->next != NULL; recur_node = recur_node->next) {}
       recur_node->next = point;
   }
   return 1;															//return 1 for successful
}


/*
 * Determine whether the specified string is in the hashtable.
 * Return 1 if it is found, 0 if it is not (or if it is null).
*/ 
int get(char *string, hashtable *h){									//for determine if the value already exists in the hashtable
    if(string == NULL || h == NULL) return 0;							//check that there is valid string and hashtable, return error 0 if there is not
    unsigned long val = 0;												//val for the hash value

    if (hash(string, &val) == 0) return 0;											//if there was a problem in the hash function return 0 for error
    val %= h->length;
    if (val < 0 || val >= h->length) return 0;						//a second check that val is within the correct range -- this should be able to be deleted

    node* recur_node = NULL;									//set the pointer to the head of this bucket
	for(recur_node = h->list[val]; recur_node != NULL; recur_node = recur_node->next){
		if (strcmp(recur_node->value, string) == 0) { return 1; }
    }
    return 0;
}

void delete_hashtable(hashtable* h){
	if (h == NULL) { return; }
  
	node** ptr = NULL;
	node* innerPtr = NULL;
	for(ptr = h->list; ptr != NULL;) {
		for(innerPtr = ptr[0]; innerPtr != NULL;){
			free(innerPtr->value);

			node* tmp = innerPtr->next;
			free(innerPtr);
			innerPtr = tmp;
		}
		node **tmp = ptr;
		tmp++;
		free(ptr);
		ptr = tmp;
	}

	free(h->list);
	free(h);
}


int resize(hashtable *h, unsigned int capacity){
	if (h == NULL) {												//if there was an error allocating memory
	   fprintf(stderr, "ERROR: resize failed:");
	   return 0;													//return error 0
	}

	//Assume success
	hashtable *hTmp = create_hashtable(capacity);
	if (hTmp == NULL) return 0;
	node** ptr = NULL;
	node* innerPtr = NULL;
	for(ptr = hTmp->list; ptr != NULL; ptr++) {
		for(innerPtr = ptr[0]; innerPtr != NULL ;innerPtr = innerPtr->next){
			if(put(innerPtr->value, hTmp) == 0) {
				delete_hashtable(hTmp);
				return 0;
			}
		}
	}

	delete_hashtable(h);
	h = hTmp;
	return 1;
}

hashtable* create_hashtable(unsigned int capacity){
  hashtable* hstar = malloc(sizeof(hashtable));
  node** array = malloc(capacity*sizeof(node*));
  if (array == NULL) {
    printf("malloc error");
    free(hstar);
    return NULL;
  }
  hstar->list = array;
  for(; array != NULL; array++) { array[0] = NULL; }		//fill the buckets with all NULL values
  hstar->length = capacity;
  return hstar;
}


