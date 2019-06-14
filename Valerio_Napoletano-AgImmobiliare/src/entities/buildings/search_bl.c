/**
 * @file search_bl.c
 * @author Saverio Valerio
 * @date 8 June 2019
 * @brief Functions for searching buildings using specific criteria.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../datatypes.h"
#include "../../consts.h"
#include "../../utils.h"

#include "show_bl.h"

/**
 * @brief Search buildings within a specific price range.
 * 
 * @param allBuildings Array of structs of all registered buildings
 * @param numBuildings Number of buildings registered
 */
void searchBuildingsForPrice(building *allBuildings, unsigned int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	double maxPrice = 0;

	clearScr();

	printSectionName("Ricerca immobili", false);

	printf("\nPrezzo massimo dell'immobile da cercare: ");
	maxPrice = readInteger();

	for (unsigned int i = 0; i < numBuildings; i++) {
		if ((allBuildings + i)->price < maxPrice) {
			found = true;
			showBuildingData(allBuildings + i);
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	newLine();
	pause();
}

/**
 * @brief Search buildings available in a specific city.
 * 
 * @param allBuildings Array of structs of all registered buildings
 * @param numBuildings Number of buildings registered
 */
void searchBuildingsForCity(building *allBuildings, unsigned int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	char city[MAX_STRING_SIZE] = "";

	clearScr();

	printSectionName("Ricerca immobili", false);

	printf("\nCitta' dov'e' situato l'immobile: ");
	readString(city, false, false);
	convertToUpperCase(city);

	for (unsigned int i = 0; i < numBuildings; i++) {
		if (strstr((allBuildings + i)->city, city) != NULL) {
			found = true;
			showBuildingData(allBuildings + i);
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	newLine();
	pause();
}

/**
 * @brief Search buildings available with a specific contract type
 * 
 * @param allBuildings Array of structs of all registered buildings
 * @param numBuildings Number of buildings registered
 */
void searchBuildingsCtrType(building *allBuildings, unsigned int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	unsigned short int ctrType = 0;

	clearScr();

	printSectionName("Ricerca immobili", false);

	printContractChoices();
	printf("\n\nSeleziona tipo di contratto: ");
	ctrType = readInteger();

	for (unsigned int i = 0; i < numBuildings; i++) {
		if ((allBuildings + i)->ctrType == ctrType) {
			found = true;
			showBuildingData(allBuildings + i);
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	newLine();
	pause();
}

/**
 * @brief Search buildings available with a specific type
 * 
 * @param allBuildings Array of structs of all registered buildings
 * @param numBuildings Number of buildings registered
 */
void searchBuildingsByType(building *allBuildings, unsigned int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	unsigned short int buildingType = 0;

	clearScr();

	printSectionName("Ricerca immobili", false);
	newLine();
	printBuildingChoices();
	printf("\n\nSeleziona tipo di immobile: ");
	buildingType = readInteger();
	
	for (unsigned int i = 0; i < numBuildings; i++) {
		if ((allBuildings + i)->builType == buildingType) {
			found = true;
			showBuildingData(allBuildings + i);
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	newLine();
	pause();
}

/**
 * @brief Search for a specific building using a criteria.
 *
 * @param allBuildings Array of structs of all registered buildings.
 * @param numBuildings Number of buildings registered.
 */
int searchBuilding(building *allBuildings, unsigned int numBuildings) {
	bool error = false;
	unsigned short int choice = 0;

	clearScr();
	printSectionName("Ricerca immobili", false);

	if (numBuildings != 0) {
		do {
			newLine();

			puts("Scegli un criterio:");
			puts("1. Prezzo massimo");
			puts("2. Localita'");
			puts("3. Tipologia contratto");
			puts("4. Tipologia immobile");
			puts("5. Torna indietro");

			newLine();
			printf("Criterio: ");
			choice = readInteger();

			switch (choice) {
				case 1:
					searchBuildingsForPrice(allBuildings, numBuildings);
					break;
				case 2:
					searchBuildingsForCity(allBuildings, numBuildings);
					break;
				case 3:
					searchBuildingsCtrType(allBuildings, numBuildings);
					break;
				case 4:
					searchBuildingsByType(allBuildings, numBuildings);
					break;
				case 5:
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
	} else {
		dbEmptyError();
		pause();
	}

	return -1;
}
