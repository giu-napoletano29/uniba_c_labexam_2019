/**
 * @file utils.h
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Contains general purpose functions that can be useful in various sections of the software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> /** For printFormattedDate() */

/** Only for getting STRING_SIZE constant */
#include "datatypes.h"

/**
 * Just print a new line to the console
 */
void newLine() {
	printf("\n");
}

/**
 * @brief Clear the console emulator screen (multiplatform)
 *
 * This function is able to "clean" the console buffer.
 * It's compatible with Windows and Unix based operating systems (GNU/Linux, macOS, etc..)
 * thanks to the usage of the Pre-defined Compiler Macros.
 *
 * @see https://sourceforge.net/p/predef/wiki/OperatingSystems/
 * @see http://port70.net/~nsz/c/c11/n1570.html#6.10.1p1
 */
void clearScr() {
#if defined(_WIN32)
	system("cls");
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
		system("clear");
#endif
}

/**
 * @brief Check if the string has any number.
 *
 * @param str String to check
 * @return true has a number or false does not have a number.
 */
bool isNumber(char *str) {
	bool numFound = false;
	for (int i = 0; i < strlen(str); i++) {
		/** isdigit: Non-zero value if the character is a numeric character, zero otherwise. */
		if (isdigit(str[i]) != 0) {
			numFound = true;
		}
	}
	return numFound;
}

/**
 * @brief Read a string from stdin with input checks.
 *
 * @param numCheck If true makes sure that the string does not have any numbers in it (input validation)
 * @return str_result Result struct with value and error (check out datatypes.h)
 */
str_result readString(bool numCheck) {
	/** Struct for handling errors and the inserted value */
	str_result readValue;

	/**
	 * Boolean for detecting if string is correct
	 * false = string is correct
	 * true = string is not correct, ask again the user
	 */
	readValue.error = false;

	// TODO: Handle spaces.
	// STRING_SIZE is 50, then limit scanf to 50 characters
	scanf("%50s", readValue.val);

	/**
	 * Check if any number can be found in the string.
	 * Only if numCheck bool is true.
	 */
	if (numCheck && isNumber(readValue.val)) {
		puts("\nInserisci una stringa corretta. \n");
		readValue.error = true;
	}

	return readValue;
}

/**
 * @brief Check if any character can be found in the string.
 *
 * @param str String to check.
 * @return true if char has been found in the string, otherwise return false.
 */
bool isChar(char *str) {
	bool charFound = false;
	for (int i = 0; i < strlen(str); i++) {
		/** isalpha: Non-zero value if the character is a numeric character, zero otherwise. */
		if (isalpha(str[i]) != 0) {
			charFound = true;
		}
	}
	return charFound;
}

/**
 * @brief Read a string from stdin (with input checks) and convert to an integer.
 *
 * @return int_result Result struct with value and error (check out datatypes.h)
 */
int_result readInteger() {
	/** Struct for handling errors and the inserted value */
	int_result readValue;

	/**
	 * Boolean for detecting if string is correct
	 * false = string is correct
	 * true = string is not correct, ask again the user
	 */
	readValue.error = false;

	/**	Internal string buffer */
	char buffer[STRING_SIZE];

	/** Read from stdin (as a string) */
	scanf("%s", buffer);

	/** Check if there are any numbers in the string. */
	if (isChar(buffer)) {
		puts("\nInserisci un numero corretto. \n");
		readValue.error = true;
	}

	if (!readValue.error) {
		/** If no errors are found, convert to integer. */
		readValue.val = atoi(buffer);
	}

	return readValue;
}

/**
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

/**
 * Convert every char in the string to uppercase
 *
 * @param str String to convert to uppercase.
 */
void convertToUpperCase(char *str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		str[i] = toupper(str[i]);
	}
}

/**
 * Set custom colors to stdout using ANSI escape codes.
 *
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
 * @return true bool string is equal, false bool string is not equal
 */
bool strCompare(char *from, char *to) {
	bool result = false;

	/**
	 * Using the conditional operator
	 * @see https://en.wikipedia.org/wiki/%3F:#C
	 */
	result = strcmp(from, to) == 0 ? true : false;

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
		scanf("%1s", usrInput);

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
