/**
 * @file menus.c
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Various menus for linking together program's modules.
 */

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#include "agency.h"
#include "entities/buildings/files_bl.h"
#include "entities/buildings/misc_bl.h"
#include "entities/buildings/show_bl.h"
#include "entities/clients/files_cl.h"
#include "entities/clients/misc_cl.h"
#include "entities/clients/req_cl.h"
#include "entities/clients/show_cl.h"
#include "entities/pros/files_pr.h"
#include "entities/pros/misc_pr.h"
#include "entities/pros/show_pr.h"
#include "sort.h"

/**
 * @brief Initialize the main allClients data structure and show the "clients" menu.
 *
 * - Declares and initialises the array of structs,"client" type.
 * - Shows the main clients menu asking the user what wants to do.
 *
 * @param reloadFile If true
 * @return
 */
int clientsMenu(bool reloadFile) {
	short int choice;
	bool error = false;

	/** Declare and initialize the array of structs, "client" type */
	int clientsNum = getClientsNumber();
	client allClients[clientsNum];
	initClientsArray(allClients, clientsNum);

	/** Load and parse client file */
	loadClientFile(allClients);

	/**
	 Check if there's any client with duplicated IDs
	 If so asks the user to change it. */
	checkDuplicateClients(allClients, clientsNum);

	do {
		clearScr();

		newLine();

		if (error) {
			notFoundError();
		}

		if (!reloadFile) {
			setGreenColor();
			puts("--- CLIENTI ---");
			resetColor();
			newLine();

			puts("Scegli un'operazione:");
			puts("1. Visualizza tutti i clienti");
			puts("2. Aggiungi un cliente");
			puts("3. Torna indietro");

			newLine();

			printf("Operazione: ");
			choice = readInteger();
		} else {
			// Auto "jump" to the first switch case for reloading the file and sorting it.
			choice = 1;
		}

		switch (choice) {
		case 1:
			// Sort clients in the file
			choice = sortFileCli(allClients, clientsNum);

			// Show all clients only if it's explicitly asked by the user.
			if (!reloadFile) {
				choice = showAllClients(allClients, clientsNum);
			}
			break;
		case 2:
			choice = addClient();
			clientsMenu(true);
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
	} while (error == true);

	// -1 for going back to the
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
			notFoundError();
		}

		setGreenColor();
		puts("--- PROFESSIONISTI ---");
		resetColor();
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Mostra tutti i professionisti");
		//puts("2. Aggiungi un professionista");
		//puts("3. Modifica un professionista");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		choice = readInteger();

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
			/*case 2:
			 //choice = addPro();
			 break;
			 case 3:
			 //choice = editPro();
			 break;*/
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
			notFoundError();
		}

		setGreenColor();
		puts("--- IMMOBILI ---");
		resetColor();
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
		choice = readInteger();

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
			/*case 2:
			 //choice = addBuilding();
			 break;
			 case 3:
			 //choice = editBuilding();
			 break;
			 case 4:
			 //choice = removeBuilding();
			 break;*/
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
			notFoundError();
		}

		setCyanColor();
		puts(
				"||| Agenzia Immobiliare di Saverio Valerio e Giuseppe Napoletano |||\n");
		setGreenColor();
		puts("--- MENU PRINCIPALE ---");
		resetColor();
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Clienti");
		puts("2. Professionisti");
		puts("3. Immobili");

		newLine();

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
		case 1:
			choice = clientsMenu(false);
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
