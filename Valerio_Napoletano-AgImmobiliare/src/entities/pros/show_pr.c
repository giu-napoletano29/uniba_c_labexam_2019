/*
 * clients_show.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"
#include "files_pr.h"

void showProData(professional *pr) {
	//puts("--- RIEPILOGO ---");
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
	//pause();
}

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
