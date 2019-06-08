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
 * @param num_records Number of professionals/potentials saved in the array.
 */
void showProData(professional *pr, potential *allPts, int num_records) {
	setCyanColor();
	printf("Codice fiscale: ");
	resetColor();
	printf("%s \n", pr->id);

	setCyanColor();
	printf("Nome: ");
	resetColor();
	printf("%s \n", pr->name);

	setCyanColor();
	printf("Cognome: ");
	resetColor();
	printf("%s \n", pr->surname);

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
	printFormattedDate(pr->reg_date);

	setCyanColor();
	printf("Immobili venduti: ");
	resetColor();
	printf("%d \n", pr->buildings_sold);

	// Print related potential
	findPotential(pr->id, allPts, num_records);
}

/**
 * @brief Print every client available in the array of structs.
 * Iterates on num_pros calling the showProData() function.
 *
 * @param allPros Array of structs of all registerd professionals
 * @param allPts Array of structs of all registered potentials
 * @param num_records Number of professionals/potentials saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllPros(professional *allPros, potential *allPts, int num_records) {
	int i;

	sortPros(allPros, num_records);
	rewriteProsToFile(allPros, num_records);

	clearScr();
	printSectionName("Lista professionisti", false);

	if (num_records != 0) {
		for (i = 0; i < num_records; i++) {
			setCyanColor();
			printf("\n-- PROFESSIONISTA %d --\n", i + 1);
			resetColor();

			showProData((allPros + i), allPts, num_records);
		}
	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
