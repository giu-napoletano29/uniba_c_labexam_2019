/**
 * @file req_cl.c
 * @author Saverio Valerio
 * @date 2 June 2019
 * @brief Functions file containing prototypes related to the "request buildings' data" functions.
 */

#include <stdio.h>
#include <string.h>
// Boolean (introduced in C99)
#include <stdbool.h>
#include <stdlib.h>
#include <time.h> // For using time(null)

#include "../../utils.h"
#include "../../datatypes.h"
#include "../../consts.h"
#include "show_bl.h" // For using printBuildingChoices()

/**
 * @brief Generate building's ID and set in the struct.
 *
 * @param bl "building" type struct
 */
void genBuildingID(building *bl) {
	int rand_num = 0;
	srand(time(NULL));

	// Limit number to 9
	rand_num = rand();

	bl->id = rand_num;
}

/**
 * @brief Request building's street name and civic number from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingStreet(building *bl) {
	//TODO: Only checks are both false for reading spaces
	printf("\nVia/Piazza/Viale: ");
	readString(bl->street, false, false);

	printf("\nNumero civico: ");
	bl->civic = readInteger();
	clearScr();
}

/**
 * @brief Request building's city from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingCity(building *bl) {
	printf("Citta': ");
	readString(bl->city, false, false);
	clearScr();
}

/**
 * @brief Request building's province from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingProvince(building *bl) {
	bool error = false;

	printf("Provincia (come sigla): ");
	do {
		if (readString(bl->province, true, false) != 2) {
			error = true;
			setYellowColor();
			puts("\nValore errato!");
			printf("Inserisci la sigla di una provincia (es. BT): ");
			resetColor();
		} else {
			error = false;
		}
	} while (error == true);
	clearScr();
}

/**
 * @brief Request building's price from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingPrice(building *bl) {
	printf("Prezzo in euro: ");
	bl->price = readDouble();
	
	clearScr();
}

/**
 * @brief Request building's owner name from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingOwner(building *bl) {
	printf("Nome e cognome proprietario: ");
	//TODO: Only checks are both false for reading spaces
	readString(bl->owner, false, false);
	clearScr();
}

/**
 * @brief Request building's owner phone number from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingPhone(building *bl) {
	printf("Numero telefono proprietario: ");
	readString(bl->phone, false, true);
	clearScr();
}

/**
 * @brief Request building's type from stdin.
 *
 * @param bl "building" type struct
 */
void reqBuildingType(building *bl) {
	bool error = false;

	printBuildingChoices();

	newLine();

	do {
		newLine();

		if (error) {
			notFoundError();
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		bl->b_type = readInteger();

		if (bl->b_type < 1 || bl->b_type > 5) {
			error = true;
		}
	} while (bl->b_type < 1 || bl->b_type > 5);
}
