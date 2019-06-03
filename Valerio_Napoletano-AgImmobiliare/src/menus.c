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
 * @param reloadFile If true this function is called back again "recursively" for loading the updated data.
 * @return -1 for going back to the main menu.
 */
int clientsMenu(bool reloadFile) {
	short int choice;
	bool error = false;

	/** - Declare and initialize the array of structs, "client" type */
	int clientsNum = getClientsNumber();
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

		newLine();

		if (error) {
			notFoundError();
		}

		/** - Shows the main clients menu asking the user what wants to do. */
		if (!reloadFile) {
			setGreenColor();
			printSectionName("Clienti");
			resetColor();
			newLine();

			puts("Scegli un'operazione:");
			puts("1. Visualizza tutti i clienti");
			puts("2. Aggiungi un cliente");
			puts("3. Elimina un cliente");
			puts("4. Torna indietro");

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
				//TODO: Add rewrite for sortFile
				break;
			case 2:
				// Append a new client to the file.
				choice = addClient();
				// Call again the function for loading the new updated data.
				clientsMenu(true);
				break;
			case 3:
				choice = deleteClient(allClients, clientsNum);
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

	return -1;
}

/**
 * @brief Initialize the main allProfessionals data structure and show the "professionals" menu.
 * @return -1 for going back to the main menu.
 */
int professMenu() {
	short int choice;
	bool error = false;

	/** - Declare and initialize the array of structs, "professional" type */
	int professionalsNum = getProfessionalsNumber();
	professional allProfessionals[professionalsNum];
	initProsArray(allProfessionals, professionalsNum);

	/** - Load pros file and stores the parsed data in the memory. */
	loadProsFile(allProfessionals);

	/**
	 - Check if there's any client with duplicated IDs
	 If so asks the user to change it. */
	checkDuplicatePros(allProfessionals, professionalsNum);

	do {
		clearScr();

		newLine();

		if (error) {
			notFoundError();
		}

		setGreenColor();
		printSectionName("Professionisti");
		resetColor();
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Mostra tutti i professionisti");
		puts("2. Torna indietro");

		newLine();

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
			case 1:
				choice = showAllPros(allProfessionals, professionalsNum);
				sortFilePro(allProfessionals, professionalsNum);
				rewriteProfessionalsToFile(allProfessionals, professionalsNum);
				break;
			case 2:
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

/**
 * @brief Initialize the main allBuildings data structure and show the "buildings" menu.
 * @return -1 for going back to the main menu.
 */
int buildingsMenu() {
	short int choice;
	bool error = false;

	/** - Declare and initialize the array of structs, "building" type */
	int buildingsNum = getBuildingsNumber();
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

		newLine();

		if (error) {
			notFoundError();
		}

		setGreenColor();
		printSectionName("Immobili");
		resetColor();
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Visualizza tutti gli immobili");
		puts("2. Cerca un immobile");
		puts("3. Aggiungi un immobile");
		puts("4. Elimina un immobile");
		puts("5. Risultati agenzia");
		puts("6. Torna indietro");

		newLine();

		printf("Operazione: ");
		choice = readInteger();

		switch (choice) {
			case 1:
				choice = showAllBuildings(allBuildings, buildingsNum);
				sortFileBui(allBuildings, buildingsNum);
				rewriteBuildingsToFile(allBuildings, buildingsNum);
				break;
			case 2:
				choice = searchBuilding(allBuildings, buildingsNum);
				break;
			case 3:
				choice = addBuilding();
				break;
			case 4:
				// Delete building
				break;
			case 5:
				choice = resultsAgency(allBuildings, buildingsNum);
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

/**
 * @brief Main menu of the software. Connects the various clients, pros and buildings submenus.
 */
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

		puts("||| Agenzia Immobiliare di Saverio Valerio e Giuseppe Napoletano |||\n");
		printSectionName("Menu principale");
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
