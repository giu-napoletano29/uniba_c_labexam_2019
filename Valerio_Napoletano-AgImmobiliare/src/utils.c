/**
 * @file utils.c
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Contains general purpose functions that can be useful in various sections of the software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> // For printFormattedDate()

// Only for getting MAX_STRING_SIZE constant
#include "datatypes.h"

/**
 * @brief Just print a new line to the console
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
 * @brief Reset custom color on stdout to its default using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void resetColor() {
	printf("\033[0m");
}

/**
 * @brief Set red color to stdout using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void setRedColor() {
	printf("\033[1;31m");
}

/**
 * @brief Set yellow color to stdout using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void setYellowColor() {
	printf("\033[01;33m");
}

/**
 * @brief Set cyan color to stdout using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void setCyanColor() {
	printf("\033[1;36m");
}

/**
 * @brief Set green color to stdout using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void setGreenColor() {
	printf("\033[0;32m");
}

/**
 * @brief Set magenta color to stdout using ANSI escape codes.
 *
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
void setMagentaColor() {
	printf("\033[1;35m");
}

/**
 * @brief Check if the string has only alphabetic characters.
 * i.e either an uppercase letter (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 * or a lowercase letter (abcdefghijklmnopqrstuvwxyz)
 *
 * @param str String to check
 * @return true if string is only made up by alphabetic characters, false otherwise.
 */
bool isOnlyAlpha(char *str) {
	bool result = false;
	for (int i = 0; i < strlen(str); i++) {
		/*! isalpha: Non-zero value if the character is a numeric character
		 *  zero otherwise. */
		if (isalpha(str[i]) == 0) {
			result = true;
		}
	}
	return result;
}

/**
 * @brief Check if any character can be found in the string.
 *
 * @param str String to check.
 * @return true if char has been found in the string, otherwise return false.
 */
bool anyChar(char *str) {
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
 * @brief Read a string from stdin with input checks.
 *
 * Parameters onlyAlpha and onlyNumbers are useful for input validation.
 * Keep in mind that "onlyAlpha" does not allow spaces in the string.
 *
 * @param value Value from stdin to store in memory.
 * @param onlyAlpha If true allows only alphabetical letters in the string.
 * @param onlyNumbers If true allows only digits in the string.
 * @return int String length. If returned int is -1 an error has occurred.
 */
int readString(char *value, bool onlyAlpha, bool onlyNumbers) {
	bool error = false;
	char inputVal[MAX_STRING_SIZE];

	do {
		// Read from stdin
		fgets(inputVal, sizeof(inputVal), stdin);
		// Format the string removing the useless \n
		sscanf(inputVal, "%[^\n]", inputVal);

		if (onlyAlpha && isOnlyAlpha(inputVal)) {
			error = true;
			setYellowColor();
			puts("\nValore errato.\nInserisci una stringa corretta senza spazi e premi Invio: ");
			resetColor();
		} else if (onlyNumbers && anyChar(inputVal)) {
			error = true;
			setYellowColor();
			puts("\nValore errato.\nInserisci solo cifre senza spazi e premi Invio: ");
			resetColor();
		} else {
			error = false;
		}
	} while (error == true);

	strcpy(value, inputVal);

	return strlen(inputVal);
}

/**
 * @brief Read a string from stdin with input checks and convert to an integer.
 *
 * @return int Integer from stdin. -1 if an unrecoverable error is detected.
 */
int readInteger() {
	bool error = false;

	/**	Define an internal string buffer. */
	char buffer[MAX_STRING_SIZE];
	/**  Initialize value to -1 for representing a possible error state. */
	int value = -1;

	do {
// Read from stdin
		fgets(buffer, sizeof(buffer), stdin);
// Format the string removing the useless \n
		sscanf(buffer, "%[^\n]", buffer);

		/** Check if there are any numbers in the string. */
		if (anyChar(buffer)) {
			error = true;
			setYellowColor();
			puts("\nInserisci un numero corretto e premi Invio: ");
			resetColor();
		} else {
			/** If no errors are found, convert to integer. */
			value = atoi(buffer);
			error = false;
		}
	} while (error == true);

	return value;
}

/**
 * @brief Print date formatted in day/month/year.
 *
 * @param epochTime UNIX Epoch Time value
 * @see https://en.wikipedia.org/wiki/Unix_time
 */
void printFormattedDate(time_t epochTime) {
	/**
	 * Declare pointer to time struct for handling UNIX Epoch time
	 */
	struct tm *clDate;

	/**
	 * Declare buffer for printing out the date (required by strftime)
	 *  day/month/year (eg. 22/05/2019)
	 */
	char dateBuffer[11];

	/**
	 *  Fill time struct getting date/time info from the UNIX Epoch time
	 */
	clDate = localtime(&epochTime);

	/**
	 * Format date and put in dateBuffer for printing out
	 */
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);
	puts(dateBuffer);
}

/**
 * @brief Convert every char in the string to uppercase
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
 * @brief System pause highlighted in yellow.
 */
void pause() {
	setYellowColor();
	system("PAUSE");
	resetColor();
}

/**
 * @brief Show "not found" error highlighted in red.
 */
void notFoundError() {
	setRedColor();
	puts("Tipologia non trovata, per favore riprova.\n");
	resetColor();
}

/**
 * Set console window title
 * Works only on Windows
 * @param titleToSet String to set as the console window's title.
 */
void setTitle(char *titleToSet) {
	char command[MAX_TEXT_SIZE];
	char defaultName[MAX_STRING_SIZE];

	strcpy(defaultName, "Agenzia Immobiliare");

	// For string concatenation
	snprintf(command, sizeof command, "%s %s - %s", "title", titleToSet, defaultName);

	system(command);
}

/**
 * @brief Print in the console the formatted "section name".
 *
 * @param string Section name to display.
 * @param isHome Shows the program title if true
 */
void printSectionName(char *string, bool isHome) {
	// Set the console window title
	setTitle(string);

	// Show only if isHome boolean is true
	if (isHome) {
		setCyanColor();
		puts("||| Agenzia Immobiliare di Saverio Valerio e Giuseppe Napoletano |||\n");
		resetColor();
	}

	printf("||| ");

	setGreenColor();
	printf("%s", string);

	resetColor();
	printf(" |||");
	newLine();
}

/**
 * @brief Prettier and easy to use wrapper for string comparison.
 *
 * @param from First string to compare
 * @param to Second string to compare
 * @return true bool string is equal, false bool string is not equal
 */
bool strCompare(char *from, char *to) {
	bool result = false;

	/**
	 * Using the conditional operator.
	 * @see https://en.wikipedia.org/wiki/%3F:#C
	 */
	result = strcmp(from, to) == 0 ? true : false;

	return result;
}

/**
 * @brief Ask user for yes or no confirmation.
 *
 * @return true if user confirmed the choice, false the user refused.
 */
bool askConfirm() {
	/** Declare array of 2 positions for keeping the newline "\n" */
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
			printf("\nScelta non valida.\nInserisci una scelta corretta (s o n) e premi Invio: ");
			resetColor();
		}
	} while (error == true);

	return choice;
}

/**
 * Print DB empty error to stdout
 */
void dbEmptyError() {
	setRedColor();
	printf("\nERRORE: Nessun record presente nel database.\n\n");
	resetColor();
}
