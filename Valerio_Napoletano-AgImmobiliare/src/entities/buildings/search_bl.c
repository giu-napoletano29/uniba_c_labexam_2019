/*
 * search_bl.c
 *
 *  Created on: 8 giu 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../datatypes.h"
#include "../../consts.h"
#include "../../utils.h"

#include "show_bl.h"

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

			setCyanColor();
			printf("--- IMMOBILE %d ---\n", (allBuildings + i)->id);
			resetColor();
			showBuildingData(allBuildings + i);
			
			newLine();
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	pause();
}

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

			setCyanColor();
			printf("--- IMMOBILE %d ---\n", (allBuildings + i)->id);
			resetColor();
			showBuildingData(allBuildings + i);

			newLine();
		}
	}

	if (!found) {
		setYellowColor();
		printf("\nNessun record trovato.\n");
		resetColor();
	}

	pause();
}

