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
 * @param numRecords Number of professionals/potentials registered
 */
void findPotential(char id[], potential *pr, int numRecords) {
	for (int i = 0; i < numRecords; i++) {
		if (strCompare(id, (pr + i)->id)) {
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
 * @param filePtr Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 */
void parsePotentialsFile(FILE *filePtr, potential *pr) {
	char line[MAX_TEXT_SIZE];
	char *token;

	int field;
	// Pros counter
	int proNum = 0;

	while (fgets(line, sizeof line, filePtr) != NULL) /* read a line */
	{
		// Fields counter (ID, name, etc..)
		field = 0;

		/**
		 * The delimiter used is the pipe symbol ( | ) instead of the comma.
		 * This is for avoiding any conflict from an user that might insert the comma
		 * because the "potential" is text.
		 */
		// Tokenize and load in the internal struct
		// Get first token
		token = strtok(line, "|");

		while (token != NULL) {
			switch (field) {
				case 0:
					strcpy((pr + proNum)->id, token);
					break;
				case 1:
					strcpy((pr + proNum)->content, token);
					break;
			}
			// Read the other tokens
			token = strtok(NULL, "|");
			field++;
		}
		proNum++;
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

/**
 * @brief Append a new potential to the "pros_potential.dat" file
 *
 * @param pt Potential struct where the data is stored
 * @return -1 go back to main menu
 */
int appendPtsToFile(potential *pt) {
	FILE *filePtr;
	filePtr = fopen("pros_potential.dat", "a+");

	if (checkFile(filePtr)) {
		// Save to file only if the potential is not marked for deletion
		if (!pt->toDelete) {
			// Write professionals file
			fprintf(filePtr, "%s|%s\n", pt->id, pt->content);
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Replace potentials file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param allPts Potentials array of structs where the data is stored
 * @param rows How many potentials are registered
 */
void rewritePtsToFile(potential *allPts, int rows) {
	FILE *filePtr;
	filePtr = fopen("pros_potential.dat", "w+");

	if (checkFile(filePtr)) {
		rewind(filePtr);
		for (int i = 0; i < rows; i++) {
			// Write to file only if toDelete bool is false
			if (!(allPts + i)->toDelete) {
				fprintf(filePtr, "%s|%s\n", (allPts + i)->id, (allPts + i)->content);
			}
		}
	}

	fclose(filePtr);
}
