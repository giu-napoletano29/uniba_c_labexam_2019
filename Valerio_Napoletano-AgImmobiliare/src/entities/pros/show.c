/*
 * clients_show.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

void showProData(professionals *pr) {
	//puts("--- RIEPILOGO ---");
	printf("Codice fiscale: %s \n", pr->id);
	printf("Nome: %s \n", pr->name);
	printf("Cognome: %s \n", pr->surname);
	printf("Area di competenza: %s \n", pr->area);
	printf("Numero di telefono: %s \n", pr->phone);
	printf("Indirizzo e-mail: %s \n", pr->email);
	printf("Data di registrazione: %hd/%hd/%hd \n", pr->reg_date.day,
			pr->reg_date.month, pr->reg_date.year);
	printf("Immobili venduti: %d \n", pr->buildings_sold);

	newLine();
	system("pause");
}

int showAllPros(professionals *pr, int num_pros) {
	int i;

	clearScr();
	puts("--- LISTA PROFESSIONISTI ---");
	for (i = 0; i < num_pros; i++) {
		printf("\n-- PROFESSIONISTA %d --\n", i + 1);
		showProData(pr+i);
	}

	return -1;
}
