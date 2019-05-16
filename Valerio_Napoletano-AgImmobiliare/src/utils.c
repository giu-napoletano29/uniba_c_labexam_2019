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

// Read a string from stdin with input checks
bool readString(char *buffer, bool numCheck) {
	// Boolean for detecting if string is correct
	// false = string is correct
	// true = string is not correct, ask again the user
	bool error = false;

	// STRING_SIZE is 50, then limit scanf to 50 characters
	scanf("%50s", buffer);

	// Check if there are any numbers in the string
	// Only if the flag numCheck is active
	if (numCheck && isNumber(buffer)) {
		puts("\nInserisci una stringa corretta. \n");
		error = true;
	}

	return error;
}

// Check if there is any characters in the string
bool isChar(char *str) {
	bool charFound = false;
	for (int i = 0; i < strlen(str); i++) {
		//isalpha: Non-zero value if the character is a numeric character, zero otherwise.
		if (isalpha(str[i]) != 0) {
			charFound = true;
		}
	}
	return charFound;
}

// Read an integer from stdin with input checks
bool readInteger(int *result_num, bool charCheck) {
	// Boolean for detecting if number is correct
	// false = string is correct
	// true = string is not correct, ask again the user
	bool error = false;
	int num;

	// Internal string buffer
	char buffer[STRING_SIZE];

	// Read from stdin (as a string)
	scanf("%50s", buffer);

	// Check if there are any numbers in the string
	// Only if the flag numCheck is active
	if (charCheck && isChar(buffer)) {
		puts("\nInserisci un numero corretto. \n");
		error = true;
	}

	if (!error) {
		// If no error are found, convert to integer.

		num = atoi(buffer);
		result_num = &num;
	}

	return error;
}
