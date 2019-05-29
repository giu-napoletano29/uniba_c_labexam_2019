/**
 * @file show.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for "showing" data to the user related to the buildings.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

/**
 * Print out a string with the building type.
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
 * Print every field present in a building struct.
 *
 * @param bl building type struct
 */
void showBuildingData(building *bl) {
	setCyanColor();
	printf("Identificativo: ");
	resetColor();
	printf("%s \n", bl->id);

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
	printf("%d euro \n", bl->price);

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
 * Print every building available in the array of structs.
 * Iterates on num_buildings calling the showBuildingData() function.
 *
 * @param bl Array of structs (building type)
 * @param num_buildings Number of items (buildings) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllBuildings(building *bl, int num_buildings) {
	int i;

	clearScr();
	printSectionName("LISTA IMMOBILI");

	for (i = 0; i < num_buildings; i++) {
		setCyanColor();
		printf("\n-- IMMOBILE %d --\n", i + 1);
		resetColor();
		showBuildingData(bl + i);
	}
	newLine();
	pause();
	return -1;
}
