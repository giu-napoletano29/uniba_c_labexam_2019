/*
 * utils.c
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Only for getting STRING_SIZE constant
#include "datatypes.h"

// Just print a new line to the console
void newLine() {
	printf("\n");
}

// Clear the console emulator screen (multiplatform)
void clearScr() {
	// Macros from https://sourceforge.net/p/predef/wiki/OperatingSystems/
	// "defined": http://port70.net/~nsz/c/c11/n1570.html#6.10.1p1
	#if defined(_WIN32)
		// Windows
		system("cls");
	#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
		// Unix based systems (GNU/Linux, macOS, etc..)
		system("clear");
	#endif
}

// Check if there is any number in the string
bool isNumber(char *str) {
	bool numFound = false;
	for (int i = 0; i < strlen(str); i++) {
		//isdigit: Non-zero value if the character is a numeric character, zero otherwise.
		if (isdigit(str[i]) != 0) {
			numFound = true;
		}
	}
	return numFound;
}

// Read properly a string from stdin
bool readString(char *buffer, bool numCheck) {
	// Boolean for detecting if string is correct
	// false = string is correct
	// true = string is not correct, ask again the user
	bool error = false;

	// Workaround: remove newline character not detected by scanf for making fgets work properly
	// "Any trailing white space (including <newline> characters) shall be left unread unless matched by a conversion specification."
	// http://pubs.opengroup.org/onlinepubs/9699919799/functions/scanf.html
	fgetc(stdin);

	// Get the string and directly write to memory
	fgets(buffer, STRING_SIZE, stdin);

	// Remove \n registerd with fgets
	// https://www.freebsd.org/cgi/man.cgi?query=strcspn&sektion=3
	buffer[strcspn(buffer, "\n")] = 0;

	// Check if there are any numbers in the string
	// Only if the flag numCheck is active
	if (numCheck && isNumber(buffer)) {
		puts("\nInserisci una stringa corretta. \n");
		error = true;
	}

	return error;
}
