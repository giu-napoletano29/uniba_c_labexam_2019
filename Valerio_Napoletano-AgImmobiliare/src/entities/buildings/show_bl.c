/**
 * @file show_bl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for "showing" data to the user related to the buildings.
 */

#include <stdio.h>
#include <stdlib.h>

#include "files_bl.h"

#include "../../utils.h"
#include "../../sort.h"
#include "../../datatypes.h"

/**
 * @brief Print out a string with the building type.
 * Check out the "buildingType" in datatypes.h
 *
 * @param type Integer that represents the building type.
 */
void showBuildingType(unsigned short int type) {
	switch (type) {
		case 1:
			printf("Appartamento");
			break;
		case 2:
			printf("Appartamento a due piani");
			break;
		case 3:
			printf("Villa");
			break;
		case 4:
			printf("Casa di campagna");
			break;
		case 5:
			printf("Attico");
			break;
		default:
			printf("Dato non corretto");
			break;
	}

	printf("\n");
}

/**
 * @brief Print out a string with the contract type.
 * Check out "contractType" in datatypes.h
 *
 * @param type Integer that represents the contract type.
 */
void showContractType(unsigned short int type) {
	switch (type) {
		case 1:
			printf("Affitto");
			break;
		case 2:
			printf("Vendita");
			break;
		default:
			printf("Dato non corretto");
			break;
	}

	printf("\n");
}

/**
 * Print to stdout available building type choices.
 */
void printBuildingChoices() {
	printf("Tipologia immobile da cercare: ");
	newLine();
	printf("1. Appartamento");
	newLine();
	printf("2. Appartamento a due piani");
	newLine();
	printf("3. Villa");
	newLine();
	printf("4. Casa di campagna");
	newLine();
	printf("5. Attico");
}

/**
 * Print to stdout available contract type choices.
 */
void printContractChoices() {
	printf("\nTipologia contratto: ");
	newLine();
	printf("1. Affitto");
	newLine();
	printf("2. Vendita");
}

/**
 * @brief Print every field present in a building struct.
 *
 * @param bl building type struct
 */
void showBuildingData(building *bl) {
	setCyanColor();
	printf("\n-- IMMOBILE ID %d --\n", bl->id);
	printf("Tipo contratto: ");
	setYellowColor();
	showContractType(bl->ctrType);
	resetColor();

	setCyanColor();
	printf("Indirizzo: ");
	resetColor();
	printf("%s, %d \n", bl->street, bl->civic);

	setCyanColor();
	printf("Citta': ");
	resetColor();
	printf("%s (%s)\n", bl->city, bl->province);

	setCyanColor();
	printf("Data di registrazione: ");
	resetColor();
	printFormattedDate(bl->regDate);

	setCyanColor();
	printf("Prezzo: ");
	setYellowColor();
	printf("%.2f euro \n", bl->price);
	resetColor();

	setCyanColor();
	printf("Proprietario: ");
	resetColor();
	printf("%s (tel. %s)\n", bl->owner, bl->phone);

	setCyanColor();
	printf("Tipologia: ");
	setYellowColor();
	showBuildingType(bl->builType);
	resetColor();

	setCyanColor();
	if (bl->ctrType == 1) {
		printf("Affittato: ");
	} else if (bl->ctrType == 2) {
		printf("Venduto: ");
	}
	if (bl->soldOn != 0) {
		setGreenColor();
		printf("Si', il giorno ");
		printFormattedDate(bl->soldOn);
	} else {
		setRedColor();
		printf("No\n");
	}
	resetColor();

}

/**
 * @brief Print every building available in the array of structs.
 * Iterates on numBuildings calling the showBuildingData() function.
 *
 * @param bl Array of structs (building type)
 * @param numBuildings Number of items (buildings) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllBuildings(building *bl, unsigned int numBuildings) {
	clearScr();
	printSectionName("Lista immobili", false);

	// Sort and rewrite to file building only if needed
	if (numBuildings > 1) {
		sortBuildings(bl, numBuildings);
		rewriteBuildingsToFile(bl, numBuildings, BUILDINGS_FNAME);
	}

	if (numBuildings != 0) {
		for (unsigned int i = 0; i < numBuildings; i++) {
			showBuildingData(bl + i);
		}
		newLine();
	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
