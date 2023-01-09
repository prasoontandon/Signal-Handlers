////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      mySigHandler.c, division.c
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
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

/* Main function that allows user to send signals.
 *
 * argc number of command line arguments
 * argv command line arguments
 */
int main(int argc, char *argv[]) {
	//Error checking: 3 args expected, one of which is the executable file
	if(argc != 3) {
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(1);
	}

	pid_t pid = atoi(argv[2]); //pid of process user wants to send signal to
	if(strcmp(argv[1], "-u") == 0) { //-u for SIGUSR1
		if(kill(pid, SIGUSR1) != 0) {
			printf("Error with kill() in sendsig.c with -u flag\n");
			exit(1);
		}

	} else if(strcmp(argv[1], "-i") == 0) { //-i for SIGINT
		if(kill(pid, SIGINT) != 0) {
			printf("Error with kill() in sendsig.c with -i flag\n");
		}

	} else { //Invalid input case
		printf("Usage: signal type must be -u or -i\n");
		exit(1);
	}
}
