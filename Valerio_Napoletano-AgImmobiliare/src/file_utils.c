/*
 * fileutils.c
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /** For parseDateInFile() */

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"

/**
 * Check if the file can be written and if it's empty
 * @param filePtr
 * @return bool error
 */
bool checkFile(FILE *filePtr) {
	bool error = false;
	int rows = 0;

	rows = countRows(filePtr);

	if (filePtr == NULL) {
		setRedColor();
		perror("\nERRORE: ");
		resetColor();
		printf("\nControlla il tuo file system e riprova.\n");
		error = true;
		system("pause");
	}

	// Check if the file is empty
	if (rows == 0) {
		setRedColor();
		printf("\nERRORE: Nessun record presente nel database.\n\n");
		resetColor();
		error = true;
		fclose(filePtr);
		system("pause");
	}

	return error;
}

int countRows(FILE *filePtr) {
	int count = 0;
	char line[400];
	while (fgets(line, sizeof line, filePtr) != NULL) /* read a line */
	{
		// Testing
		//printf("%d. ", count + 1);
		//fputs(line, stdout); /* write the line */
		count++;
	}

	// Testing
	//printf("\nRecord trovati nel file: %d\n", count);
	//system("pause");

	return count;
}

time_t parseDateInFile(char token[STRING_SIZE]) {
	/*
	 * Temp "tm" struct required for parsing the date properly from the file
	 */
	struct tm temp_date = { 0 };

	/**
	 * Parse date in Italian format (day/month/year)
	 */

	sscanf(token, "%d/%d/%d", &temp_date.tm_mday, &temp_date.tm_mon,
			&temp_date.tm_year);

	/*
	 * tm_mon is defined as a range between 0 to 11.
	 * tm_year starts from 1900.
	 *
	 * @see http://www.cplusplus.com/reference/ctime/tm/
	 */
	temp_date.tm_mon -= 1;
	temp_date.tm_year -= 1900;

	return mktime(&temp_date);
}
