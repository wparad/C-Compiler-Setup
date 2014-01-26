/* 
 * File:   hashtable-test.c
 * Author: Parad
 *
 * Created on January 22, 2014, 6:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*
 * 
 */
int main(int argc, char *argv[] ) {
   
/* 													//left over from completing the lab1
    hashtable h1;
    int i = 0;
    for(i = 0; i < CAPACITY; i++) { h1.list[i] = NULL;}
    unsigned long test = 0;
    int x = 0;
    x = hash("cat",&test);
    printf("%ld \n",test);
    x = hash("dogasdf",&test);
    printf("%ld \n",test);
    x = put("dogaaaaaaaaaaaaaaaaaa",&h1);
    printf("%d \n",x);
    x = put("dog",&h1);
    printf("%d \n", x);
    x = get("cat",&h1);
    printf("%d \n", x);
    x = put("cat",&h1);
    printf("%d \n", x);
    x = get("cat",&h1);
    printf("%d \n", x);
    x = get("dog",&h1);
    printf("%d \n", x);
    printf("DONE");
    return 0;
}	
*/
  
 // if (argc != 3){
 //   printf("please input 2 file names as command line arguments for this program.\n");
 // }else {
  
    unsigned int length = 3;                        //set the initial length of the hashtable array
  
	char userinput1[250];										//for the first file name
	char userinput2[250];										//for the second file name
	char file_word[257];
    FILE *src_file1;											//pointer for link to first file
	printf("Please enter the name of the first file\n");
	scanf("%s", userinput1);
	printf("Please enter the name of the second file\n");
	scanf("%s", userinput2);									//get input for second file

	src_file1 = fopen(userinput1, "rb");				//link first file
	if(src_file1 == NULL) { return 1; }								//if file doesn't link, return error 1

	//create a hashtable
	hashtable* h1 = create_hashtable(length);

    while (fscanf(src_file1, "%s", file_word) != EOF){			//get next word and continue until end of file
        put(file_word,h1);										//call put on hashtable 1
	}
    fclose(src_file1);  //close opened files

    src_file1 = fopen(userinput2,"rb");
	if(src_file1 == NULL) return 1;								//if file doesn't link, return error 1

    //create hashtable 2
    hashtable* h2 = create_hashtable(length);
    
    while (fscanf(src_file1, "%s", file_word) != EOF){			//get next word and continue until end of file
        put(file_word,h2);										//call put on hashtable 2
    }
    fclose(src_file1);

	int matches = 0;											//int to determine matches between file 1 and 2
	node* one = NULL;											//for iterating through hashtable 1
    int i = 0;
	for(i=0; i < h1->length; i++){									//for all buckets in the hashtable
		one = h1->list[i];										//one is the first node in that bucket
		while (one != NULL) {									//while there exists another node
          matches += get(one->value, h2);		//if there is a value at that node, and that value is in hashtable 2, increment
          one = one->next;															//move to next node
		}
	}

	printf("The number of matches is %d",matches);				

    delete_hashtable(h1);
    delete_hashtable(h2);

    scanf("%s", userinput2);
    return 0;
}



