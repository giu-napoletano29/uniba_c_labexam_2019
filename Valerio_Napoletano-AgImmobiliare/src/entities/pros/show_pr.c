/**
 * @file show_pr.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for printing out professionals information.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"
#include "files_pr.h"

//TODO: Maybe should be removed
#include "files_pts.h"

/**
 * @brief Print every field available in a professional struct.
 *
 * @param pr professional type struct
 */
void showProData(professional *pr) {
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

	//TODO: Program crashes if no potentials are available for the clients
	//TODO: TO UPDATE
	//loadPotentialsFile(pr->id);
}

/**
 * @brief Print every client available in the array of structs.
 * Iterates on num_pros calling the showProData() function.
 *
 * @param pros Array of structs (professional type)
 * @param num_pros Number of items (professionals) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllPros(professional *pros, int num_pros) {
	int i;

	clearScr();
	printSectionName("Lista professionisti", false);

	if (num_pros != 0) {
		for (i = 0; i < num_pros; i++) {
			setCyanColor();
			printf("\n-- PROFESSIONISTA %d --\n", i + 1);
			resetColor();
			showProData(pros + i);
		}
	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
