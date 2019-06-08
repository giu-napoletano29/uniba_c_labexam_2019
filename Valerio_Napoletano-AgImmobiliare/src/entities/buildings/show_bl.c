/**
 * @file show_bl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for "showing" data to the user related to the buildings.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

/**
 * @brief Print out a string with the building type.
 * Check out the "building_type" in datatypes.h
 *
 * @param type Integer that represents the building type.
 */
void showBuildingType(int type) {
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
 * @brief Print every field present in a building struct.
 *
 * @param bl building type struct
 */
void showBuildingData(building *bl) {
	setCyanColor();
	printf("Identificativo: ");
	resetColor();
	printf("%d \n", bl->id);

	setCyanColor();
	printf("Indirizzo: ");
	resetColor();
	printf("%s \n", bl->street);

	setCyanColor();
	printf("Numero civico: ");
	resetColor();
	printf("%d \n", bl->civic);

	setCyanColor();
	printf("Citta': ");
	resetColor();
	printf("%s \n", bl->city);

	setCyanColor();
	printf("Provincia: ");
	resetColor();
	printf("%s \n", bl->province);

	setCyanColor();
	printf("Data di registrazione: ");
	resetColor();
	printFormattedDate(bl->reg_date);

	setCyanColor();
	printf("Prezzo: ");
	resetColor();
	printf("%.2f euro \n", bl->price);

	setCyanColor();
	printf("Venditore: ");
	resetColor();
	printf("%s \n", bl->owner);

	setCyanColor();
	printf("Numero di telefono venditore: ");
	resetColor();
	printf("%s \n", bl->phone);

	setCyanColor();
	printf("Tipologia: ");
	resetColor();
	showBuildingType(bl->b_type);
}

/**
 * @brief Print every building available in the array of structs.
 * Iterates on numBuildings calling the showBuildingData() function.
 *
 * @param bl Array of structs (building type)
 * @param numBuildings Number of items (buildings) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllBuildings(building *bl, int numBuildings) {
	int i;

	clearScr();
	printSectionName("Lista immobili", false);

	if (numBuildings != 0) {
		for (i = 0; i < numBuildings; i++) {
			setCyanColor();
			printf("\n-- IMMOBILE %d --\n", i + 1);
			resetColor();
			showBuildingData(bl + i);
		}
		newLine();
	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
