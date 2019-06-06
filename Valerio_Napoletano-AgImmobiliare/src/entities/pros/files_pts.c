/**
 * @file files_pts.c
 * @author Saverio Valerio
 * @date 6 June 2019
 * @brief Functions for handling the CSV file related to the professionals' "potential".
 */

#include <stdio.h>
#include <string.h>

#include "../../utils.h"
#include "../../datatypes.h"
#include "../../file_utils.h"

/**
 * @brief Print potential string of a specific professional.
 * The "potential" of a pro is a simple string that explains what are his "strenghts".
 * E.g. "He's able to sell quickly houses located on the beach."
 *
 * @param id Professional's ID
 * @param pr Potentials array of structs
 * @param num_records Number of professionals/potentials registered
 */
void findPotential(char id[], potential *pr, int num_records) {
	for (int i = 0; i < num_records; i++) {
		if (strCompare(id, pr[i].id)) {
			setCyanColor();
			printf("Potenziale: ");
			resetColor();
			printf("%s \n", (pr + i)->content);
		}
	}
}

/**
 * @brief Parse "potential" file (pros_potential.dat)
 * Check out findPotential() for more information about the "potential".
 *
 * @param fp_pot Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 */
void parsePotentialsFile(FILE *fp_pot, potential *pr) {
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
}

/**
 * @brief Initialize potential array of structs and parse professionals' potential file.
 *
 * @param allPotentials Array of structs (potential datatype) where data will be stored.
 */
void loadPotentialsFile(potential *allPotentials) {
	FILE *filePtr;

	filePtr = fopen("pros_potential.dat", "a+");

	if (checkFile(filePtr)) {
		rewind(filePtr);

		parsePotentialsFile(filePtr, allPotentials);
	}

	fclose(filePtr);
}
