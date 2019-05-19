/*
 * menus.c
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdbool.h>

#include "menus.h"
#include "utils.h"
#include "fileop.h"

#include "entities/clients.h"

void mainMenu() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		puts("-- Agenzia Immobiliare --");
		puts("- MENU PRINCIPALE -");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Clienti");
		puts("2. Professionisti");
		puts("3. Immobili");

		newLine();

		printf("Operazione: ");
		// short integer placeholder is %hu
		// ISO/IEC 9899:201x - 7.21.6.1-7
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = clientsMenu();
			break;
		case 2:
			choice = professMenu();
			break;
		case 3:
			choice = propertyMenu();
			break;
		default:
			error = true;
			break;
		}
	} while (error == true || choice == -1);
}

int clientsMenu() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		puts("--- CLIENTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un cliente");
		puts("2. Modifica un cliente");
		puts("3. Cerca un cliente");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = addClient();
			break;
		case 2:
			//choice = editClient();
			break;
		case 3:
			//choice = searchClientMenu();
			break;
		case 4:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -1;
			error = false;
			break;
		default:
			error = true;
			break;
		}
	} while (error == true);

	// Go back
	return -1;
}

int professMenu() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		puts("--- PROFESSIONISTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un professionista");
		puts("2. Modifica un professionista");
		puts("3. Cerca un professionista");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			//choice = addClient();
			break;
		case 2:
			//choice = professMenu();
			break;
		case 3:
			//choice = propertyMenu();
			break;
		case 4:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -1;
			error = false;
			break;
		default:
			error = true;
			break;
		}

	} while (error == true);
	return choice;
}

int propertyMenu() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		puts("--- IMMOBILI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un immobile");
		puts("2. Modifica un immobile");
		puts("3. Cancella un immobile");
		puts("4. Cerca un immobile");
		puts("5. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
			choice = addbuild();
			break;
		case 2:
			choice = editbuild();
			break;
		case 3:
			choice = removebuild();
			break;
		case 4:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -1;
			error = false;
			break;
		default:
			error = true;
			break;
		}

	} while (error == true);
	return choice;
}
