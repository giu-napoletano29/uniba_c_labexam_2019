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
#include "datatypes.h"

//TODO: Refer to line 54, should be removed
//#include "entities/buildings.h"

int checkFile(FILE *fp_build) {
	int res = 0;

	if (fp_build == NULL) {
		printf(
				"\n------------------------ ATTENZIONE ------------------------");
		perror("\nErrore: ");
		printf("\nControlla il tuo file system e riprova.\n");
		res = 1;
		fclose(fp_build);
		system("pause");
	}

	return res;
}

int countRows(FILE *fp_build) {
	int count = 0;
	char line[400];
	while (fgets(line, sizeof line, fp_build) != NULL) /* read a line */
	{
		// Testing
		//printf("%d. ", count + 1);
		//fputs(line, stdout); /* write the line */
		count++;
	}

	// Testing
	//printf("\nRecord trovati nel file: %d\n", count);

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

/*
 void copyFile(FILE *fp_from, FILE *fp_to, int choice) {
 char line[400];
 unsigned int Uchoice = -choice;
 int count = 0;
 // Read a line
 while (fgets(line, sizeof line, fp_from) != NULL)
 {
 count++;
 if (choice == 0) {
 fputs(line, fp_to);
 } else if (choice > 0) {
 if (choice == count) {
 // TODO: This should not be here, the function should be "object" agnostic
 infoBuilding(fp_to);
 } else {
 fputs(line, fp_to);
 }
 } else {
 if (Uchoice != count) {
 fputs(line, fp_to);
 }
 }
 }
 }
 */
