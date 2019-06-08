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
		(bl + i)->reg_date = 0;
		(bl + i)->price = 0;
		strcpy((bl + i)->owner, "");
		strcpy((bl + i)->phone, "");
		(bl + i)->b_type = flat;
    (bl + i)->sold = false;
	}
}

/**
 * @brief Get current system date and save the UNIX Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param bl "building" type struct
 */
void saveBuildingLocalDate(building *bl) {
	time_t timeRightNow;

	// time function returns the current Epoch time (time_t)
	bl->reg_date = time(&timeRightNow);
}

/**
 * @brief Append a building to the buildings file.
 * Initializes a client struct and calls the "req" functions for filling the latter.
 *
 * @return -1 for going back to the main menu.
 */
int addBuilding() {
	building bl = { 0, "", 0, "", "", 0, 0, "", "", 1, 0 };

	clearScr();
	printSectionName("Aggiunta immobile", false);

	genBuildingID(&bl);

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
 * Delete a building identified by his ID inputted by the user.
 *
 * @param allBuildings Array of structs of all buildings registered.
 * @param numBuildings Number of buildings registered.
 * @return -1 for going back to the menu
 */
int deleteBuilding(building *allBuildings, int numBuildings) {
	bool found = false;

	clearScr();
	printSectionName("Eliminazione immobile", false);

	int toDeleteID;
	printf("\nInserisci identiticativo immobile da eliminare: ");
	toDeleteID = readInteger();

	for (int i = 0; i < numBuildings; i++) {
		if (toDeleteID == (allBuildings + i)->id) {
			(allBuildings + i)->toDelete = true;
			found = true;
		}
	}

	if (found) {
		rewriteBuildingsToFile(allBuildings, numBuildings);
		setGreenColor();
		printf("\nImmobile eliminato!\n");
		resetColor();
	} else {
		setRedColor();
		printf("\nNessun immobile trovato con l'ID inserito.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}
