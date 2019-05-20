/*
 * fileutils.c
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "datatypes.h"

//TODO: Refer to line 54, should be removed
#include "entities/properties.h"

int checkFile(FILE *fp_build) {
	int res = 0;

	if (fp_build == NULL) {
		printf("\n------------------------ ATTENZIONE ------------------------");
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
		printf("%d. ", count + 1);
		fputs(line, stdout); /* write the line */
		count++;
	}
	return count;
}

void copyFile(FILE *fp_from, FILE *fp_to, int choice) {
	char line[400];
	unsigned int Uchoice = -choice;
	int count = 0;
	while (fgets(line, sizeof line, fp_from) != NULL) /* read a line */
	{
		count++;
		if (choice == 0) {
			fputs(line, fp_to);
		} else if (choice > 0) {
			if (choice == count) {
				// TODO: This should not be here, the function should be "object" agnostic
				infoBuild(fp_to);
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
