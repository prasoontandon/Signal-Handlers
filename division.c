////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      mySigHandler.c, sendsig.c
// Semester:         CS 354 Lecture 002 Fall 2022
// Instructor:       deppeler
// 
// Author:           Prasoon Tandon
// Email:            ptandon3@wisc.edu
// CS Login:         tandon
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

const int BUFFER = 100; //size of input expected from user
int SUCCESS_CNT = 0; //keep track of successfull divisons

/* Custom handler for SIGFPE signal that's different from default.
 *
 * Requires being properly bound/registered elsewhere.
 */
void handler_SIGFPE() {
	printf("Error: a division by 0 operation was attempted.\n"
			"Total number of operations completed successfully: %i\n"
			"The program will be terminated.\n", SUCCESS_CNT);
	exit(0);
}

/* Custom handler for SIGINT signal that's different from default. 
 *
 * Requires being properly bound/registered elsewhere.
 */
void handler_SIGINT() {
	printf("\nTotal number of operations completed successfully: %i\n"
			"The program will be terminated.\n", SUCCESS_CNT);
	exit(0);
}

/* This is method is responsible for running the division appliciation
 * and binding signals appropriately.
 */
int main() {
	//Register signal handler for SIGFPE	
	struct sigaction sa_fpe;
	memset(&sa_fpe, 0, sizeof(sa_fpe));
	sa_fpe.sa_handler = handler_SIGFPE;
	if(sigaction(SIGFPE, &sa_fpe, NULL) != 0) {
		printf("Error binding SIGFPE handler\n");
		exit(1);
	}

	//Register signal handler for SIGINT
	struct sigaction sa_int;
     memset(&sa_int, 0, sizeof(sa_int));
     sa_int.sa_handler = handler_SIGINT; 
     if(sigaction(SIGINT, &sa_int, NULL) != 0) {
         printf("Error binding SIGINT handler\n");
         exit(1);
     }
	
	//Infinite loop to interact with user
	while(1) {
		char frst_input[BUFFER];
		char scnd_input[BUFFER];
		//get first input
		printf("Enter first integer: ");
		if(fgets(frst_input, BUFFER, stdin) == NULL) {
			printf("Error in reading first integer!\n");
			exit(1);
		} 		
		//get second input
		printf("Enter second integer: ");
		if(fgets(scnd_input, BUFFER, stdin) == NULL) {
			printf("Error in reading second integer!\n");
			exit(1);
		}		
		//convert input to integer values
		int num1 = atoi(frst_input);
		int num2 = atoi(scnd_input);
		//output as expected
		printf("%i / %i is %i with a remainder of %i\n", 
				num1, num2, (num1 / num2), (num1 % num2));
		SUCCESS_CNT++;
	}
}
