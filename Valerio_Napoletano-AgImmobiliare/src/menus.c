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
#include "entities/buildings/show.h"
#include "entities/buildings/misc.h"

#include "entities/pros/files.h"
#include "entities/pros/show.h"
#include "entities/pros/misc.h"

#include "agency.h"
#include "sort.h"

int clientsMenu(int jump) {
	short int choice;
	short int resDup = 0;
	bool error = false;

	// INITIALIZE client array of structs
	int clientsNum = getClientsNumber();
	client allClients[clientsNum];
	initClientsArray(allClients, clientsNum);

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		if (jump == 0) {
			puts("--- CLIENTI ---");
			newLine();

			puts("Scegli un'operazione:");
			puts("1. Visualizza tutti i clienti");
			puts("2. Aggiungi un cliente");
			//puts("3. Cancella clienti");
			puts("4. Torna indietro");

			newLine();

			printf("Operazione: ");
			scanf("%hu", &choice);
		} else {
			choice = jump;
		}

		switch (choice) {
		case 1:
			choice = loadClientFile(allClients);
			resDup = checkDuplicateClients(allClients, clientsNum);
			if (resDup != -1) {
				showAllClients(allClients, clientsNum);
				sortFileCli(allClients, clientsNum);
				//TODO: Optimize: run only if some clients needs to be deleted
				rewriteClientsToFile(allClients, clientsNum);
			}
			break;
		case 2:
			choice = addClient();
			resDup = clientsMenu(1);
			break;
		case 3:
			//choice = deleteClient();
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
	short int resDup = 0;
	bool error = false;

	int professionalsNum = getProfessionalsNumber();

	professional allProfessionals[professionalsNum];
	initProsArray(allProfessionals, professionalsNum);

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		puts("--- PROFESSIONISTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Mostra tutti i professionisti");
		//puts("2. Aggiungi un professionista");
		//puts("3. Modifica un professionista");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadProsFile(allProfessionals);
			resDup = checkDuplicatePro(allProfessionals, professionalsNum);
			if (resDup != -1) {
				showAllPros(allProfessionals, professionalsNum);
				sortFilePro(allProfessionals, professionalsNum);
				rewriteProfessionalsToFile(allProfessionals, professionalsNum);
			}
			break;
		case 2:
			//choice = addPro();
			break;
		case 3:
			//choice = editPro();
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

int buildingsMenu() {
	short int choice;
	short int resDup = 0; //check for duplicate id

	int buildingsNum = getBuildingsNumber();
	building allBuildings[buildingsNum];
	initBuildingsArray(allBuildings, buildingsNum);

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
		//puts("2. Aggiungi un immobile");
		//puts("3. Modifica un immobile");
		//puts("4. Cancella un immobile");
		puts("5. Cerca un immobile");
		puts("6. Risultati agenzia");
		puts("7. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadBuildingsFile(allBuildings);
			resDup = checkDuplicateBuildings(allBuildings, buildingsNum);
			if (resDup != -1) {
				showAllBuildings(allBuildings, buildingsNum);
				sortFileBui(allBuildings, buildingsNum);
				rewriteBuildingsToFile(allBuildings, buildingsNum);
			}

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
			choice = loadBuildingsFile(allBuildings);
			resDup = checkDuplicateBuildings(allBuildings, buildingsNum);
			if (resDup != -1) {
				searchBuilding(allBuildings, buildingsNum);
			}
			break;
		case 6:
			choice = loadBuildingsFile(allBuildings);
			resDup = checkDuplicateBuildings(allBuildings, buildingsNum);
			if (resDup != -1) {
				resultAg(allBuildings, buildingsNum);
			}
			break;
		case 7:
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
			choice = clientsMenu(0);
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
