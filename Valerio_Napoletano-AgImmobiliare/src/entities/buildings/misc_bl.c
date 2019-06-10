/**
 * @file misc_bl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief File containing misc functions used by the "building" entity.
 */

#include <string.h>

#include "../../datatypes.h"
#include "req_bl.h"
#include "show_bl.h"
#include "files_bl.h"
#include "../../utils.h"

/**
 * @brief Initialize an array of structs of buildings.
 *
 * @param bl "building" type array of struct.
 * @param size How many elements the array of struct will keep.
 */
void initBuildingsArray(building *bl, int size) {
	for (int i = 0; i < size; i++) {
		(bl + i)->id = 0;
		strcpy((bl + i)->street, "");
		(bl + i)->civic = 0;
		strcpy((bl + i)->city, "");
		strcpy((bl + i)->province, "");
		(bl + i)->regDate = 0;
		(bl + i)->price = 0;
		strcpy((bl + i)->owner, "");
		strcpy((bl + i)->phone, "");
		(bl + i)->builType = flat;
		(bl + i)->soldOn = 0;
	}
}

/**
 * @brief Get current system date and save the UNIX Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param bl "building" type struct
 */
void saveBuildingLocalDate(building *bl) {
	time_t timeRightNow = 0;

	// time function returns the current Epoch time (time_t)
	bl->regDate = time(&timeRightNow);
}

void checkDuplicateIDbl(building *bl, building *allBuildings, int numBuildings) {
	bool error = false;
	do {
		if (error) {
			setYellowColor();
			puts("\nQuesto ID e' gia' presente nel database.\nSi prega di inserirne uno diverso.\n");
			resetColor();
		}
		genBuildingID(bl);

		for (int i = 0; i < numBuildings; i++) {
			if (bl->id == (allBuildings + i)->id) {
				error = true;
				i = numBuildings;
			} else {
				error = false;
			}
		}

	} while (error == true);
}

/**
 * @brief Append a building to the buildings file.
 * Initializes a client struct and calls the "req" functions for filling the latter.
 *
 * @return -1 for going back to the main menu.
 */
int addBuilding(building *allBuildings, int numBuildings) {
	building bl = { 0, "", 0, "", "", 0, 0, "", "", 1, 0 };

	clearScr();
	printSectionName("Aggiunta immobile", false);

	checkDuplicateIDbl(&bl, allBuildings, numBuildings);

	reqContractType(&bl);

	reqBuildingStreet(&bl);

	reqBuildingCity(&bl);

	reqBuildingProvince(&bl);

	reqBuildingPrice(&bl);

	reqBuildingOwner(&bl);

	reqBuildingPhone(&bl);

	reqBuildingType(&bl);

	reqBuildingSold(&bl);

	saveBuildingLocalDate(&bl);

	appendBuildingToFile(&bl);

	return -1;
}

/**
 * Edit a building identified by his ID inputted by the user.
 *
 * @param allBuildings Array of structs of all buildings registered.
 * @param numBuildings Number of buildings registered.
 * @return -1 for going back to the menu
 */
int editBuilding(building *allBuildings, int numBuildings) {
	unsigned int toEditID = 0;
	unsigned int buildingPos = 0;
	bool found = false;

	clearScr();
	printSectionName("Modifica immobile", false);

	printf("\nInserisci identiticativo immobile da modificare: ");
	toEditID = readInteger();

	for (int i = 0; i < numBuildings; i++) {
		if (toEditID == (allBuildings + i)->id) {
			buildingPos = i;
			found = true;
		}
	}

	if (found && (allBuildings + buildingPos)->soldOn != 0) {
		/**
		 * It does not make any sense to allow the editing of the address, city, province
		 * because it would just be a completely different building.
		 */

		setCyanColor();
		printf("\nTipo contratto attuale: ");
		resetColor();
		showContractType((allBuildings + buildingPos)->ctrType);
		reqContractType(allBuildings + buildingPos);

		setCyanColor();
		printf("\nPrezzo attuale: ");
		resetColor();
		printf("%0.2f\n", (allBuildings + buildingPos)->price);
		newLine();
		reqBuildingPrice(allBuildings + buildingPos);

		setCyanColor();
		printf("\nProprietario attuale: ");
		resetColor();
		printf("%s\n", (allBuildings + buildingPos)->owner);
		newLine();
		reqBuildingOwner(allBuildings + buildingPos);

		setCyanColor();
		printf("\nTel. proprietario attuale: ");
		resetColor();
		printf("%s\n", (allBuildings + buildingPos)->phone);
		newLine();
		reqBuildingPhone(allBuildings + buildingPos);

		rewriteBuildingsToFile(allBuildings, numBuildings);
	} else {
		setRedColor();
		printf("\nNessun immobile trovato con l'ID inserito\noppure risulta venduto.");
		resetColor();
		pause();
	}
	return -1;
}

/**
 * Delete a building identified by his ID inputted by the user.
 *
 * @param allBuildings Array of structs of all buildings registered.
 * @param numBuildings Number of buildings registered.
 * @return -1 for going back to the menu
 */
int deleteBuilding(building *allBuildings, int numBuildings) {
	int toDeleteID = 0;
	bool found = false;

	clearScr();
	printSectionName("Eliminazione immobile", false);

	printf("\nInserisci identiticativo immobile da eliminare: ");
	toDeleteID = readInteger();

	for (int i = 0; i < numBuildings; i++) {
		if (toDeleteID == (allBuildings + i)->id) {
			(allBuildings + i)->toDelete = true;
			found = true;

			showBuildingData(allBuildings + i);
		}
	}

	if (found) {
		setYellowColor();
		printf("\nSei sicuro di voler cancellare l'immobile selezionato? (s/n): ");
		resetColor();
		if (askConfirm()) {
			rewriteBuildingsToFile(allBuildings, numBuildings);
			setRedColor();
			printf("\nImmobile eliminato!\n");
			resetColor();
		}
	} else {
		setRedColor();
		printf("\nNessun immobile trovato con l'ID inserito.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}

/**
 * A building can be sold or rented to a specific client.
 * This function sets the soldOn attribute in order to determine if the contract has been completed.
 *
 * @param allBuildings Array of structs of all buildings registered.
 * @param numBuildings Number of buildings registered.
 * @return -1 for going back to the menu
 */
int sellBuilding(building *allBuildings, int numBuildings) {
	int buildingID = 0;
	char soldOnString[MAX_STRING_SIZE] = "";
	bool found = false;

	clearScr();
	printSectionName("Vendita/affitto immobile", false);

	printf("\nInserisci identiticativo immobile: ");
	buildingID = readInteger();

	for (int i = 0; i < numBuildings; i++) {
		if (buildingID == (allBuildings + i)->id && (allBuildings + i)->soldOn == 0) {

			showBuildingData(allBuildings + i);

			printf("\nInserisci la data di vendita/inizio affitto (gg/mm/yyyy): ");
			readString(soldOnString, false, false);
			(allBuildings + i)->soldOn = parseDate(soldOnString);

			found = true;
		}
	}

	if (found) {
		// Update the file only if needed
		rewriteBuildingsToFile(allBuildings, numBuildings);
	} else {
		setRedColor();
		printf("\nNessun immobile trovato con l'ID inserito\noppure risulta gia' venduto.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}
