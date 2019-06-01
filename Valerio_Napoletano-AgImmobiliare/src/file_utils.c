/**
 * @file file_utils.c
 * @author Giuseppe Napoletano
 * @date 13 May 2019
 * @brief Functions for making the file usage easier and more streamlined.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For parseDateInFile()

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"

/**
 * @brief Check if the file can be written and if it's empty.
 *
 * @param filePtr Pointer to file initialized by fopen()
 * @param rowsCheck If enabled the function will check if the file is empty.
 * @return true if everything is good with the file.
 */
bool checkFile(FILE *filePtr, bool rowsCheck) {
	bool error = false;
	int rows = 0;

	rows = countRows(filePtr);

	if (filePtr == NULL) {
		setRedColor();
		perror("\nERRORE: ");
		resetColor();
		printf("\nControlla il tuo file system e riprova.\n");
		error = true;
		pause();
	}

	// Check if the file is empty
	if (rowsCheck == true) {
		if (rows == 0) {
			setRedColor();
			printf("\nERRORE: Nessun record presente nel database.\n\n");
			resetColor();
			error = true;
			fclose(filePtr);
			pause();
		}
	}

	rewind(filePtr);
	return error;
}

/**
 * @brief Count rows present in the file.
 *
 * @param filePtr Pointer to file initialized by fopen()
 * @return Number of rows detected.
 */
int countRows(FILE *filePtr) {
	int count = 0;
	char line[400];
	while (fgets(line, sizeof line, filePtr) != NULL) /* read a line */
	{
		count++;
	}

	return count;
}

/**
 * @brief Parse date from a string formatted in day/month/year.
 *
 * @param string Date string to parse
 * @return time_t value (encoded in UNIX Epoch time)
 */
time_t parseDateInFile(char string[MAX_STRING_SIZE]) {
	// Temp "tm" struct required for parsing the date properly from the file
	struct tm temp_date = { 0 };

	sscanf(string, "%d/%d/%d", &temp_date.tm_mday, &temp_date.tm_mon,
			&temp_date.tm_year);

	/**
	 * tm_mon is defined as a range between 0 to 11.
	 * tm_year starts from 1900.
	 *
	 * @see http://www.cplusplus.com/reference/ctime/tm/
	 */
	temp_date.tm_mon -= 1;
	temp_date.tm_year -= 1900;

	return mktime(&temp_date);
}
