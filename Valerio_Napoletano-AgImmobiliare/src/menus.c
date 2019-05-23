/*
 * menus.c
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#include "entities/clients/misc.h"
#include "entities/clients/req.h"
#include "entities/clients/show.h"
#include "entities/clients/files.h"

#include "entities/buildings/files.h"

#include "entities/pros.h"

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
		puts("1. Visualizza tutti i clienti");
		puts("2. Aggiungi un cliente");
		puts("3. Cancella clienti");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadClientFile();
			break;
		case 2:
			choice = addClient();
			break;
		case 3:
			choice = deleteClient();
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
		puts("3. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = addPro();
			break;
		case 2:
			choice = editPro();
			break;
		case 3:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -1;
			error = false;
			break;
		default:
			error = true;
			break;
		}

	} while (error == true || choice == -2);
	return choice;
}

int buildingsMenu() {
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
		puts("1. Visualizza tutti gli immobili");
		puts("2. Aggiungi un immobile");
		puts("3. Modifica un immobile");
		puts("4. Cancella un immobile");
		puts("5. Cerca un immobile");
		puts("6. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadBuildingsFile();
			break;
		case 2:
			//choice = addBuilding();
			break;
		case 3:
			//choice = editBuilding();
			break;
		case 4:
			//choice = removeBuilding();
			break;
		case 5:
			//choice = searchBuilding();
			break;
		case 6:
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
			choice = buildingsMenu();
			break;
		default:
			error = true;
			break;
		}
	} while (error == true || choice == -1);
}
