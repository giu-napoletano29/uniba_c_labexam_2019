/*
 * buildings/show.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

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

void showBuildingData(building *bl) {
	printf("Identificativo: %s \n", bl->id);
	printf("Indirizzo: %s \n", bl->street);
	printf("Numero civico: %d \n", bl->civic);
	printf("Citta: %s \n", bl->city);
	printf("Provincia: %s \n", bl->province);
	printf("Data di registrazione: ");
	printFormattedDate(bl->reg_date);
	printf("Prezzo: %d euro \n", bl->price);
	printf("Venditore: %s \n", bl->owner);
	printf("Numero di telefono venditore: %s \n", bl->phone);
	printf("Tipologia: ");

	showBuildingType(bl->b_type);

	newLine();
	system("pause");
}

int showAllBuildings(building *bl, int num_buildings) {
	int i;

	clearScr();
	puts("--- LISTA IMMOBILI ---");
	for (i = 0; i < num_buildings; i++) {
		printf("\n-- IMMOBILE %d --\n", i + 1);
		showBuildingData(bl + i);
	}

	return -1;
}
