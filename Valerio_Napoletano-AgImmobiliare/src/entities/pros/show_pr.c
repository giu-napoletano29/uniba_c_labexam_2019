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

/**
 * @brief Print every field available in a professional struct.
 *
 * @param pr professional type struct
 */
void showProData(professional *pr) {
	printf("Codice fiscale: %s \n", pr->id);
	printf("Nome: %s \n", pr->name);
	printf("Cognome: %s \n", pr->surname);
	printf("Area di competenza: %s \n", pr->area);
	printf("Numero di telefono: %s \n", pr->phone);
	printf("Indirizzo e-mail: %s \n", pr->email);
	printf("Data di registrazione: ");
	printFormattedDate(pr->reg_date);
	printf("Immobili venduti: %d \n", pr->buildings_sold);

	printf("\nPotenziale di %s:\n", pr->name);
	loadPotFile(pr->id);
	newLine();
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
	puts("--- LISTA PROFESSIONISTI ---");
	for (i = 0; i < num_pros; i++) {
		printf("\n-- PROFESSIONISTA %d --\n", i + 1);
		showProData(pros + i);
	}
	pause();
	return -1;
}
