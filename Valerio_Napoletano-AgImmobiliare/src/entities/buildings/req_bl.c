/**
 * @file req_bl.c
 * @author Saverio Valerio
 * @date 2 June 2019
 * @brief Functions used for requesting "buildings data" to the user.
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
#include "../../file_utils.h"

#include "show_bl.h" // For using printBuildingChoices()

/**
 * @brief Generate building's ID and set in the struct.
 *
 * @param bl "building" type struct
 */
void genBuildingID(building *bl) {
	int randNum = 0;
	srand(time(NULL));

	randNum = rand();

	bl->id = randNum;
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
	convertToUpperCase(bl->street);

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
	convertToUpperCase(bl->city);
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

	convertToUpperCase(bl->province);
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
	convertToUpperCase(bl->owner);
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
		bl->builType = readInteger();

		if (bl->builType < 1 || bl->builType > 5) {
			error = true;
		}
	} while (bl->builType < 1 || bl->builType > 5);
}

/**
 * @brief Request building's contract type (rent or sale) from stdin.
 *
 * @param bl "building" type struct
 */
void reqContractType(building *bl) {
	bool error = false;

	printContractChoices();

	newLine();

	do {
		newLine();

		if (error) {
			notFoundError();
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		bl->ctrType = readInteger();

		if (bl->ctrType < 1 || bl->ctrType > 2) {
			error = true;
		}
	} while (bl->ctrType < 1 || bl->ctrType > 2);

	clearScr();
}

/**
 * @brief Request if the building has been sold (and if so, when).
 *
 * @param bl "building" type struct
 */
void reqBuildingSold(building *bl) {
	char soldOnString[MAX_STRING_SIZE] = "";

	clearScr();

	printf("L'immobile e' stato venduto/dato in affitto? (s/n): ");
	
	if (askConfirm()) {
		newLine();
		// Workaround for avoiding askConfirm() conflict with readString
		fflush(stdin);
		
		printf("Quando? Inserisci una data (gg/mm/yyyy): ");
		readString(soldOnString, false, false);
		bl->soldOn = parseDate(soldOnString);
	} else {
		bl->soldOn = 0;
	}
	
	clearScr();
}
