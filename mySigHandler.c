////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c, division.c
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
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

unsigned int SECONDS_APART = 4; //time diff for each alarm() signal
unsigned int SIGUSR1_CNTR = 0; //counter for SIGUSR1 signal

/* Custom handler for SIGINT signal that's different from default.
 * 
 * Requires being properly bound/registered elsewhere.
 */
void handler_SIGINT() {
	printf("\nSIGINT handled.\n"
		"SIGUSR1 was handled %i times. Exiting now.\n", SIGUSR1_CNTR);
	exit(0);
}

/* Custom handler for SIGALRM signal that's different from default.
 *
 * Requires being properly bound/registered elsewhere.
 */
void handler_SIGALRM() {
	const time_t time_val = time(NULL); //get time value
	if(time_val == (time_t)-1) {
		printf("Error getting time!");
		exit(1);
	}
	
	char *time_string = ctime(&time_val); //convert time to string
	if(time_string == NULL) {
		printf("Error converting time to string!");
		exit(1);
	}
	//get and print the pid of the program and the current time
	printf("PID: %d CURRENT TIME: %s", getpid(), time_string);

	alarm(SECONDS_APART); //re-arm the alarm
}

/* Custom handler for SIGUSR1 signal that's different from default.
 *
 * Requires being properly bound/registered elsewhere.
 */
void handler_SIGUSR1() {
	printf("SIGUSR1 handled and counted!\n");
	SIGUSR1_CNTR++;
}

/* Main method of the program. Responsible for binding various handlers
 * and for repeatedly sending the alarm signal.
 *
 */
int main() {

	//Register signal handler for SIGUSR1
	struct sigaction usr1_sa;
	memset(&usr1_sa, 0, sizeof(usr1_sa)); //clears all sa_flags
	usr1_sa.sa_handler = handler_SIGUSR1;
	if(sigaction(SIGUSR1, &usr1_sa, NULL) != 0) {
		printf("Error binding SIGUSR1 handler.\n");
		exit(1);
	}

	//Register signal handler for SIGINT
	struct sigaction int_sa;
	memset(&int_sa, 0, sizeof(int_sa)); //clears all sa_flags
	int_sa.sa_handler = handler_SIGINT;
	if(sigaction(SIGINT, &int_sa, NULL) != 0) {
		printf("Error binding SIGINT handler.\n");
		exit(1);
	}

	//Register signal handler for SIGALRM
	struct sigaction alrm_sa;
	memset(&alrm_sa, 0, sizeof(alrm_sa)); //clears all sa_flags
	alrm_sa.sa_handler = handler_SIGALRM;
	if(sigaction(SIGALRM, &alrm_sa, NULL) != 0) {
		printf("Error binding SIGALRM handler.\n");
		exit(1);
	}

	//Set up alarm
	alarm(SECONDS_APART);
	//Print info for user	
	printf("PID and time print every 4 seconds.\n");
	printf("Type Ctrl-C to end the program.\n");
	while(1) {
	}	

	return 0; //If reached, issue occurred
}
