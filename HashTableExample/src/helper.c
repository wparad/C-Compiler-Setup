

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
   int check = 0;	
   unsigned long val = 0;												//where the hash value will be stored
   check = hash(string, &val);										//perform hash
   val %= h->length;
   if (check == 0) return 0;											//if there is a hash error, return 0 for error
   if (!(val >=0 && val <=(h->length-1))) return 0;						//a second check that val is within the correct range -- this should be able to be deleted
   node* recur_node = h->list[val];										//node point to head of correct bucket
   node* point = malloc(sizeof(node));									//create node in the heap
   if (point == NULL) {												//if there was an error allocating memory
	   fprintf(stderr, "ERROR: create_node: malloc failed:");
	   return 0;													//return error 0
   }
   point->next = NULL;													//initialize the pointer->next value to NULL
           
   int size = strlen(string);							//find the size of the given string
    char* n_string = malloc(size*sizeof(char)+1);							//create a string in memory
    if (n_string == NULL){												//if there was an error allocating memory
        printf("Error in malloc");	
        return 0;														//return error 0
    }
   strcpy(n_string,string);       										//copy string on stack to string in heap 
           
   point->value = n_string;												//make point's value point to the string in the heap
   if (recur_node == NULL) {											//if the head pointer in the heap is null
     h->list[val] = point;												//set the head pointer to point to point (as the node of this bucket's linked list)
   } else {																//if there already exists a linked list
       while(recur_node->next != NULL) {								//while we are not at the end of the linked list
           recur_node = recur_node->next;								//move to the next node
       }
       recur_node->next = point;										//set the last node's next value to point 
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
    int check = 0;
    char* temp;															//used because I wasn't sure if strcpy could handle the -> syntax
    check = hash(string, &val);											//find the hash value for the string
    val %= h->length;
    if (check == 0) return 0;											//if there was a problem in the hash function return 0 for error
    if (!(val >=0 && val <=(h->length-1))) return 0;						//a second check that val is within the correct range -- this should be able to be deleted
    node* recur_node = h->list[val];									//set the pointer to the head of this bucket
    int final = 0;														//initialize the return value

    while(recur_node != NULL){											//while we are not at the end of the of the bucket
      if (recur_node->value != NULL){ 
        temp = recur_node->value;                                       		//temp = the string at this node
        if (temp != NULL && string != NULL){
            if (strcmp(temp, string) == 0) {									//if the temp string is equal to the string that we want return
                final = 1;														//return 1 for true
                break;														
            }
        }
      }
      recur_node = recur_node->next;									//else continue to next node
    }
    return final;														
}

int delete_hashtable(hashtable* h){
  if (h == NULL) return 0;
  int i = 0;
  node* recur_node = NULL;
  node* recur_node2 = NULL;
  char* string = NULL;
  
  for(i = 0; i<h->length; i++) {
    recur_node = h->list[i];
    while(recur_node != NULL){
      recur_node2 = recur_node->next;
      string = recur_node->value;
      free(string);
      free(recur_node);
      recur_node = recur_node2;
    }
  }
  free(h);
  return 1;
}


int resize(hashtable *h, unsigned int capacity){
	if (h == NULL) {												//if there was an error allocating memory
	   fprintf(stderr, "ERROR: resize failed:");
	   return 0;													//return error 0
	}

	//Assume success
	hashtable *hTmp = NULL;
	if (create_hashtable(hTmp, capacity) == 0) return 0;
	node** ptr = NULL;
	node* innerPtr = NULL;
	for(ptr = hTmp->list; ptr != NULL; ptr++) {
		for(innerPtr = ptr[0]; innerPtr != NULL ;innerPtr++){
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

int create_hashtable(hashtable* hstar, unsigned int capacity){
  if(hstar != NULL) return 1;
  hstar = malloc(sizeof(hashtable*));
  node** array = malloc(capacity*sizeof(node*));
  if (array == NULL) {
    printf("malloc error");
    return 1;
  }
  int i = 0;													
  for(i = 0; i < capacity; i++) { array[i] = NULL; }		//fill the buckets with all NULL values
  hstar->list = array;
  hstar->length = capacity;
  return 0;
}


