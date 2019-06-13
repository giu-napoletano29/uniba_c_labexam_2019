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
void searchBuildingsForPrice(building *allBuildings, int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	double maxPrice = 0;

	clearScr();

	printSectionName("Ricerca immobili", false);

	printf("\nPrezzo massimo dell'immobile da cercare: ");
	maxPrice = readInteger();

	newLine();

	for (int i = 0; i < numBuildings; i++) {
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
void searchBuildingsForCity(building *allBuildings, int numBuildings) {
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	char city[MAX_STRING_SIZE] = "";

	clearScr();

	printSectionName("Ricerca immobili", false);

	printf("\nCitta' dov'e' situato l'immobile: ");
	readString(city, false, false);
	convertToUpperCase(city);

	newLine();

	for (int i = 0; i < numBuildings; i++) {
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

