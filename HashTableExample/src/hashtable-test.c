/* 
 * File:   hashtable-test.c
 * Author: Parad
 *
 * Created on January 22, 2014, 6:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/*
 * 
 */
int main() {

	hashtable h1;
	int i = 0;
	for(i = 0; i < CAPACITY; i++) { h1.list[i] = NULL;
	}
    unsigned long test = 0;
    int x = 0;

	x = hash("cat",&test);
   if (x == 1) printf("%ld \n",test);

    x = hash("dog",&test);
    if (x == 1) printf("%ld \n",test);
    printf("%s","help\n");

	x = put("",&h1);
	printf("%d \n",x);

	x = put("dog",&h1);
	printf("%d \n", x);

	x = put("cat",&h1);
	printf("%d \n", x);
	
	printf("DONE");
    
    return 0;
}

