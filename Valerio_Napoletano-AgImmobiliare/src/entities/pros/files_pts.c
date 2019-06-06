/*
 * files_pts.c
 *
 *  Created on: 6 giu 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <string.h>

#include "../../utils.h"
#include "../../datatypes.h"

/**
 * @brief Print potential string of a specific professional.
 * The "potential" of a pro is a simple string that explains what are his "strenghts".
 * E.g. "He's able to sell quickly houses located on the beach."
 *
 * @param id Professional's ID
 * @param pr Potentials array of structs
 * @param num_profess Number of professionals registered
 */
void findPotential(char id[], potential *pr, int num_profess) {
	for (int i = 0; i < num_profess; i++) {
		if (strCompare(id, pr[i].id)) {
			setCyanColor();
			printf("Potenziale: ");
			resetColor();
			printf("%s \n", pr[i].content);
		}
	}
}

/**
 * @brief Parse "potential" file (pros_potential.dat)
 * Check out findPotential() for more information about the "potential".
 *
 * @param fp_pot Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 * @param id ID of the professional connected to a specific potential record.
 * @param rows Number of professionals registered
 */
void parsePotentialsFile(FILE *fp_pot, potential *pr, int rows) {
	char line[MAX_TEXT_SIZE];
	char *token;

	int field;
	// Pros counter
	int pr_num = 0;

	while (fgets(line, sizeof line, fp_pot) != NULL) /* read a line */
	{
		// Fields counter (ID, name, etc..)
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
				case 0:
					strcpy(pr[pr_num].id, token);
					break;
				case 1:
					strcpy(pr[pr_num].content, token);
					break;
			}
			// Read the other tokens
			token = strtok(NULL, ",");
			field++;
		}
		pr_num++;
	}
	//TODO: Remove
	//findPotential(id, pr, rows);
}


/**
 * @brief Get how many potentials are saved in the file.
 *
 * @return Number of potentials. (integer)
 */
int getPotsNumber() {
	FILE *filePtr;
	int rows = 0;
	filePtr = fopen("pros_potential.dat", "a+");
	if (checkFile(filePtr)) {
		if (filePtr != NULL) {
			rewind(filePtr);
			rows = countRows(filePtr);
		}
	}
	fclose(filePtr);
	return rows;
}


/**
 * @brief Initialize potential array of structs and parse professionals' potential file.
 *
 * @param id ID of the professional connected to a specific potential record.
 */
void loadPotentialsFile(char id[]) {
	int rows = 0;
	FILE *fp_pot;
	fp_pot = fopen("pros_potential.dat", "a+");
	if (checkFile(fp_pot)) {
		rows = countRows(fp_pot);
		rewind(fp_pot);

		potential pr[rows];
		initPotentialsArray(pr, rows);

		parsePotentialsFile(fp_pot, pr, rows);
	}
	fclose(fp_pot);
}
