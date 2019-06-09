/**
 * @file show_pr.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for printing out professionals information.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"
#include "../../sort.h"

#include "files_pr.h"
#include "files_pts.h"

/**
 * @brief Print every field available in a professional struct.
 *
 * @param pr professional type struct
 * @param allPts Array of structs of all available potentials records
 * @param numRecords Number of professionals/potentials saved in the array.
 */
void showProData(professional *pr, potential *allPts, int numRecords) {
	setCyanColor();
	printf("\n-- PROFESSIONISTA --\n");
	printf("Codice fiscale: ");
	resetColor();
	printf("%s \n", pr->id);

	setCyanColor();
	printf("Nome e cognome: ");
	resetColor();
	printf("%s %s \n", pr->name, pr->surname);

	setCyanColor();
	printf("Area di competenza: ");
	resetColor();
	printf("%s \n", pr->area);

	setCyanColor();
	printf("Numero di telefono: ");
	resetColor();
	printf("%s \n", pr->phone);

	setCyanColor();
	printf("Indirizzo e-mail: ");
	resetColor();
	printf("%s \n", pr->email);

	setCyanColor();
	printf("Data di registrazione: ");
	resetColor();
	printFormattedDate(pr->regDate);

	setCyanColor();
	printf("Immobili venduti: ");
	resetColor();
	printf("%d \n", pr->buildingsSold);

	// Print related potential
	findPotential(pr->id, allPts, numRecords);
}

/**
 * @brief Print every client available in the array of structs.
 * Iterates on numRecords calling the showProData() function.
 *
 * @param allPros Array of structs of all registerd professionals
 * @param allPts Array of structs of all registered potentials
 * @param numRecords Number of professionals/potentials saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllPros(professional *allPros, potential *allPts, int numRecords) {
	sortPros(allPros, numRecords);
	rewriteProsToFile(allPros, numRecords);

	clearScr();
	printSectionName("Lista professionisti", false);

	if (numRecords != 0) {
		for (int i = 0; i < numRecords; i++) {
			showProData((allPros + i), allPts, numRecords);
		}
	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
