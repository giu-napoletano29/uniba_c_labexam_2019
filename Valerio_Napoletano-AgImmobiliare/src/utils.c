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
#include <time.h> /** For printFormattedDate() */

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
str_result readString(bool numCheck) {
	// Struct for handling errors and the inserted value
	str_result readValue;

	// Boolean for detecting if string is correct
	// false = string is correct
	// true = string is not correct, ask again the user
	readValue.error = false;

	// TODO: Handle spaces.
	// STRING_SIZE is 50, then limit scanf to 50 characters
	scanf("%50s", readValue.val);

	// Check if there are any numbers in the string
	// Only if the flag numCheck is active
	if (numCheck && isNumber(readValue.val)) {
		puts("\nInserisci una stringa corretta. \n");
		readValue.error = true;
	}

	return readValue;
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
int_result readInteger() {
	// Struct for handling errors and the inserted value
	int_result readValue;

	// Boolean for detecting if number is correct
	// false = string is correct
	// true = string is not correct, ask again the user
	readValue.error = false;

	// Internal string buffer
	char buffer[STRING_SIZE];

	// Read from stdin (as a string)
	scanf("%s", buffer);

	// Check if there are any numbers in the string
	// Only if the flag numCheck is active
	if (isChar(buffer)) {
		puts("\nInserisci un numero corretto. \n");
		readValue.error = true;
	}

	if (!readValue.error) {
		// If no errors are found, convert to integer.
		readValue.val = atoi(buffer);
	}

	return readValue;
}

/*
 * Print date formatted in day/month/year.
 *
 * @param time_t epochTime
 */
void printFormattedDate(time_t epochTime) {
	/**
	 * Pointer to time struct for handling Epoch time
	 */
	struct tm *clDate;

	/**
	 * Buffer for printing out the date (required by strftime)
	 *  day/month/year (eg. 22/05/2019)
	 */
	char dateBuffer[11];

	/**
	 *  Fill time struct getting date/time info from the Epoch time
	 */
	clDate = localtime(&epochTime);

	/**
	 * Format date and put in dateBuffer for printing out
	 */
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);
	puts(dateBuffer);
}

void convertToUpperCase(char *s) {
	int len = strlen(s);
	//while(*s != '\0'){
	for (int i = 0; i < len; i++) {
		s[i] = toupper(s[i]);
	}
}

/**
 * Set custom colors to stdout using ANSI escape codes
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void resetColor() {
	printf("\033[0m");
}

void setRedColor() {
	printf("\033[1;31m");
}

void setYellowColor() {
	printf("\033[01;33m");
}

void setCyanColor() {
	printf("\033[1;36m");
}

void setGreenColor() {
	printf("\033[0;32m");
}

void setMagentaColor() {
	printf("\033[1;35m");
}

/**
 * System pause highlighted in yellow.
 */
void pause() {
	setYellowColor();
	system("PAUSE");
	resetColor();
}

/**
 * Show "not found" error highlighted in red.
 */
void notFoundError() {
	setRedColor();
	puts("Tipologia non trovata, per favore riprova. \n");
	resetColor();
}

/**
 * Print in the console the formatted "section name"
 * @param string Section name to display.
 */
void printSectionName(char *string) {
	printf("||| ");
	setGreenColor();
	printf("%s", string);
	resetColor();
	printf(" |||");
	newLine();
}

/**
 * Prettier and easy to use wrapper for string comparison.
 * @param from First string to compare
 * @param to Second string to compare
 * @return true string is equal, false string is not equal
 */
bool strCompare(char *from, char *to) {
	bool result = false;

	if (strcmp(from, to) == 0) {
		result = true;
	} else {
		result = false;
	}

	return result;
}

/**
 * Ask user for yes or no confirmation.
 * @return true if user confirmed the choice, false the user refused
 */
bool askConfirm() {
	/** Array of 2 positions for keeping the newline "\n" */
	char usrInput[1];

	bool choice = false;
	bool error = false;

	do {
		scanf("%s", usrInput);

		if (strCompare(usrInput, "s") || strCompare(usrInput, "y")) {
			choice = true;
			error = false;
		} else if (!strCompare(usrInput, "n")) {
			/** Set error bool on true if user did not select s or n */
			error = true;

			setYellowColor();
			printf(
					"\nScelta non valida.\nInserisci una scelta corretta (s o n) e premi Invio: ");
			resetColor();
		}
	} while (error == true);

	return choice;
}
