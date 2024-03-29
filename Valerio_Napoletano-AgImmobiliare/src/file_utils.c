/**
 * @file file_utils.c
 * @author Giuseppe Napoletano
 * @date 13 May 2019
 * @brief Functions for making the file usage easier and more streamlined.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For parseDate()

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"

/**
 * @brief Check if the file can be written.
 * This function is useful when the file is used
 * by another process and can't be read of for permissions issue.
 *
 * @param filePtr Pointer to file initialized by fopen()
 * @return true if everything is good with the file.
 */
bool checkFile(FILE *filePtr) {
	bool status = true;

	if (filePtr == NULL) {
		setRedColor();
		perror("\nERRORE: ");
		resetColor();
		printf("\nControlla il tuo file system e riprova.\n");
		status = false;
		pause();
	}

	rewind(filePtr);
	return status;
}

/**
 * @brief Count rows present in the file.
 *
 * @param name File name (without extension)
 * @return Number of rows detected.
 */
int countFileRows(char *name) {
	FILE *filePtr;
	unsigned int rowsNum = 0;
	char line[MAX_TEXT_SIZE] = "";

	filePtr = fopen(name, "a+");
	if (checkFile(filePtr)) {
		// Just in case
		rewind(filePtr);

		while (fgets(line, sizeof line, filePtr) != NULL) /* read a line */
		{
			rowsNum++;
		}
	}
	fclose(filePtr);
	return rowsNum;
}

/**
 * @brief Save formatted date in day/month/year to file.
 *
 * @param filePtr Pointer to file opened by fopen()
 * @param epochTime UNIX Epoch Time value
 * @see https://en.wikipedia.org/wiki/Unix_time
 */
void formattedDateToFile(FILE *filePtr, time_t *epochTime) {
	/**
	 * Declare pointer to time struct for handling UNIX Epoch time
	 */
	struct tm *clDate = { 0 };

	/**
	 * Declare buffer for printing out the date (required by strftime)
	 *  day/month/year (eg. 22/05/2019)
	 */
	char dateBuffer[11] = "";

	/**
	 *  Fill time struct getting date/time info from the UNIX Epoch time
	 */
	clDate = localtime(epochTime);

	/**
	 * Format date and put in dateBuffer for printing out
	 */
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

	// Commas are required for saving the field properly in the CSV
	fprintf(filePtr, ",%s,", dateBuffer);
}
