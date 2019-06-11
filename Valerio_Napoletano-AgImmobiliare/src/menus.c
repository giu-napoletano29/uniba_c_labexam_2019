/**
 * @file menus.c
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Various menus for linking together program's modules.
 */

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"
#include "file_utils.h"
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
#include "entities/pros/files_pts.h"

/**
 * @brief Initialize the main allClients data structure and show the "clients" menu.
 *
 * @return -1 for going back to the main menu.
 */
int clientsMenu() {
	short int choice = 0;
	bool error = false;

	/** - Declare and initialize the array of structs, "client" type */
	int clientsNum = countFileRows("clients");
	client allClients[clientsNum];
	initClientsArray(allClients, clientsNum);

	/** - Load client file and stores the parsed data in the memory. */
	loadClientFile(allClients);

	/**
	 - Check if there's any client with duplicated IDs
	 If so asks the user to change it. */
	checkDuplicateClients(allClients, clientsNum);

	do {
		clearScr();

		/** - Shows the main clients menu asking the user what wants to do. */
		printSectionName("Clienti", false);

		newLine();
		puts("Scegli un'operazione:");
		puts("1. Visualizza tutti i clienti");
		puts("2. Aggiungi un cliente");
		puts("3. Elimina un cliente");
		puts("4. Torna indietro");
		newLine();

		if (error) {
			notFoundError();

			// Reset error after showing
			error = false;
		}

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
			case 1:
				choice = showAllClients(allClients, clientsNum);
				break;
			case 2:
				// Append a new client to the file.
				choice = addClient(allClients, clientsNum);
				break;
			case 3:
				choice = deleteClient(allClients, clientsNum);
				break;
			case 4:
				// This is used as a flag for the "go back" choice
				// It's not that likely that an user will manually insert -1 as a choice.
				choice = -1;
				break;
			default:
				error = true;
				break;
		}
	} while (error == true);

	return choice;
}

/**
 * @brief Initialize the main allPros data structure and show the "professionals" menu.
 * @return -1 for going back to the main menu.
 */
int professMenu() {
	short int choice = 0;
	bool error = false;

	/** - Declare and initialize the array of structs, "professional" type */
	int prosNum = countFileRows("professionals");
	professional allPros[prosNum];
	initProsArray(allPros, prosNum);

	/** - Declare and initialize the array of structs, "potentials" type */
	int potsNum = countFileRows("pros_potential");
	potential allPts[potsNum];
	initPotentialsArray(allPts, potsNum);

	/** - Load pros file and stores the parsed data in the memory. */
	loadProsFile(allPros);
	loadPotentialsFile(allPts);

	/**
	 - Check if there's any client with duplicated IDs
	 If so asks the user to change it. */
	checkDuplicatePros(allPros, allPts, prosNum);

	do {
		clearScr();

		printSectionName("Professionisti", false);

		newLine();
		puts("Scegli un'operazione:");
		puts("1. Mostra tutti i professionisti");
		puts("2. Aggiungi un professionista");
		puts("3. Elimina un professionista");
		puts("4. Torna indietro");
		newLine();

		if (error) {
			notFoundError();

			// Reset error after showing
			error = false;
		}

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
			case 1:
				choice = showAllPros(allPros, allPts, prosNum);
				break;
			case 2:
				// Append a new professional to the file.
				choice = addPro(allPros, allPts, prosNum);
				break;
			case 3:
				choice = deletePro(allPros, allPts, prosNum);
				break;
			case 4:
				// This is used as a flag for the "go back" choice
				// It's not that likely that an user will manually insert -1 as a choice.
				choice = -1;
				break;
			default:
				error = true;
				break;
		}
	} while (error == true);
	return choice;
}

/**
 * @brief Initialize the main allBuildings data structure and show the "buildings" menu.
 * @return -1 for going back to the main menu.
 */
int buildingsMenu() {
	short int choice = 0;
	bool error = false;

	/** - Declare and initialize the array of structs, "building" type */
	int buildingsNum = countFileRows("buildings");
	building allBuildings[buildingsNum];
	initBuildingsArray(allBuildings, buildingsNum);

	/** - Load buildings file and stores the parsed data in the memory. */
	loadBuildingsFile(allBuildings);

	/**
	 - Check if there's any client with duplicated IDs
	 If so asks the user to change it. */
	checkDuplicateBuildings(allBuildings, buildingsNum);

	do {
		clearScr();
		printSectionName("Immobili", false);

		newLine();
		puts("Scegli un'operazione:");
		puts("1. Visualizza tutti gli immobili");
		puts("2. Cerca un immobile");
		puts("------");
		puts("3. Aggiungi un immobile");
		puts("4. Modifica un immobile");
		puts("5. Elimina un immobile");
		puts("6. Vendi/affitta un immobile");
		puts("------");
		puts("7. Risultati di vendita agenzia");
		puts("8. Torna indietro");
		newLine();

		if (error) {
			notFoundError();

			// Reset error after showing
			error = false;
		}

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
			case 1:
				choice = showAllBuildings(allBuildings, buildingsNum);
				break;
			case 2:
				choice = searchBuilding(allBuildings, buildingsNum);
				break;
			case 3:
				choice = addBuilding(allBuildings, buildingsNum);
				break;
			case 4:
				choice = editBuilding(allBuildings, buildingsNum);
				break;
			case 5:
				choice = deleteBuilding(allBuildings, buildingsNum);
				break;
			case 6:
				choice = sellBuilding(allBuildings, buildingsNum);
				break;
			case 7:
				choice = resultsAgency(allBuildings, buildingsNum);
				break;
			case 8:
				// This is used as a flag for the "go back" choice
				// It's not that likely that an user will manually insert -1 as a choice.
				choice = -1;
				break;
			default:
				error = true;
				break;
		}

	} while (error == true);
	return choice;
}

/**
 * @brief Main menu of the software. Connects the various clients, pros and buildings submenus.
 */
void mainMenu() {
	short int choice = 0;
	bool error = false;

	do {
		clearScr();
		printSectionName("Menu principale", true);

		newLine();
		puts("Scegli un'operazione:");
		puts("1. Clienti");
		puts("2. Professionisti");
		puts("3. Immobili");
		newLine();

		if (error) {
			notFoundError();

			// Reset error after showing
			error = false;
		}

		printf("Operazione: ");
		choice = readInteger();

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
				// choice = -1 represent the "go back to main menu" value from other functions
			case -1:
				error = false;
				break;
				// choice = 0 represent the initialized value from this function
			case 0:
				error = false;
				break;
			default:
				error = true;
				break;
		}
	} while (error == true || choice == 0 || choice == -1);
}
