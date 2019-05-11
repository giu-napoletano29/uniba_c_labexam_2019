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

// Only for getting STRING_SIZE constant
#include "datatypes.h"

// Just print a new line to the console
void newLine() {
	printf("\n");
}

// Clear the console emulator screen (multiplatform)
void clearScr() {
	// Macros from https://sourceforge.net/p/predef/wiki/OperatingSystems/`
	// "defined": http://port70.net/~nsz/c/c11/n1570.html#6.10.1p1
	#if defined(_WIN32)
		// Windows
		system("cls");
	#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
			// Unix based systems (GNU/Linux, macOS, etc..)
			system("clear");
	#endif
}


// FIXME: This does not work FOR NOW
// Check if there is any number in the string
int isNumber(char s[]) {
	for (int i = 0; i < strlen(s); i++)
		if (isdigit(s[i]) == 0)
			return 0;

	return 1;
}

// Read properly a string from stdin
int readString(char *buffer) {
	// Boolean for detecting if string is correct
	// 0 = string is correct
	// 1 = string is not correct, ask again the user
	int status = 0;

	// Workaround: remove newline character not detected by scanf for making fgets work properly
	// "Any trailing white space (including <newline> characters) shall be left unread unless matched by a conversion specification."
	// http://pubs.opengroup.org/onlinepubs/9699919799/functions/scanf.html
	fgetc(stdin);

	// Get the string and directly write to memory
	fgets(buffer, STRING_SIZE, stdin);

	/* FIXME: This does not work FOR NOW
	if (isNumber(buffer) == 1) {
		printf("Inserisci una stringa corretta.");
		status = 0;
	} else {
		status = 1;
	}
	*/

	return status;
}
