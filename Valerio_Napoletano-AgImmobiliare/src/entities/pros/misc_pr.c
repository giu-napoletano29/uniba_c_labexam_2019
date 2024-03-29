/**
 * @file misc_pr.c
 * @author Saverio Valerio
 * @date 28 May 2019
 * @brief File containing misc functions used by the "professional" entity.
 */

#include <stdio.h>
#include <string.h>

#include "files_pr.h"
#include "files_pts.h"
#include "req_pr.h"
#include "show_pr.h"

#include "../../datatypes.h"
#include "../../utils.h"
#include "../../sort.h"
#include "../../file_utils.h"

/**
 * @brief Initialize an array of structs of "potentials".
 *
 * @param po "Potential" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initPotentialsArray(potential *po, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		strcpy((po + i)->id, "");
		strcpy((po + i)->content, "");
	}
}

/**
 * @brief Initialize an array of structs of professionals.
 *
 * @param pro "Professional" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initProsArray(professional *pro, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		strcpy((pro + i)->id, "");
		strcpy((pro + i)->name, "");
		strcpy((pro + i)->surname, "");
		strcpy((pro + i)->area, "");
		strcpy((pro + i)->phone, "");
		strcpy((pro + i)->email, "");
		(pro + i)->regDate = 0;
		(pro + i)->buildingsSold = 0;
	}
}

/**
 * @brief Get current system date and save the UNIX Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param pr "professional" type struct
 */
void saveLocalDatePro(professional *pr) {
	time_t timeRightNow = 0;

	// time function returns the current Epoch time (time_t)
	pr->regDate = time(&timeRightNow);
}

/**
 * @brief Request the professional ID and check that it is not already registered.
 * 
 * @param pr Professional struct that is being registered.
 * @param allPros Array of structs where all pros are available.
 * @param numRecords Number of pros registered.
 */
void checkDuplicateProID(professional *pr, professional *allPros, unsigned int numRecords) {
	bool error = false;
	do {
		if (error) {
			setYellowColor();
			puts("\nQuesto ID e' gia' presente nel database.\nSi prega di inserirne uno diverso.\n");
			resetColor();
		}
		reqProCF(pr);

		for (unsigned int i = 0; i < numRecords; i++) {
			if (strcmp(pr->id, (allPros + i)->id) == 0) {
				error = true;
				i = numRecords;
			} else {
				error = false;
			}
		}

	} while (error == true);
}

/**
 * @brief Append a professional to its file.
 * Initializes a "professional" struct and calls the "req" functions for filling the latter.
 *
 * allPros and num_pros parameters are needed
 * for calling sortPros() and rewriteProsToFile()
 *
 * @param allPros Array of structs (professional type)
 * @param allPts Array of structs (potential type)
 * @param numRecords Number of items professionals/potentials saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int addPro(professional *allPros, potential *allPts, unsigned int numRecords) {
	professional pr = { "", "", "", "", "", "", 0, 0, false };
	potential pt = { "", "" };
	unsigned int newProsNum = 0;

	clearScr();
	printSectionName("Aggiunta professionista", false);
	newLine();

	checkDuplicateProID(&pr, allPros, numRecords);

	reqProName(&pr);

	reqProSurname(&pr);

	reqProArea(&pr);

	reqProPhone(&pr);

	reqProEmail(&pr);

	reqProSoldBuildings(&pr);

	reqProPotential(&pr, &pt);

	saveLocalDatePro(&pr);

	appendProToFile(&pr, PROS_FNAME);

	appendPtsToFile(&pt, PTS_FNAME);

	newProsNum = countFileRows(PROS_FNAME);
	
	// Reload and rewrite ordered array only if required
	if (newProsNum > 1) {
		/** - Sort professionls in the memory */
		sortPros(allPros, numRecords);

		/** - Re-declare and re-initialize the array of structs with the newly created pros */
		professional newAllPros[newProsNum];
		initProsArray(newAllPros, newProsNum);

		/** - Reload pros file and stores the parsed data in the memory. */
		loadProsFile(newAllPros, PROS_FNAME);

		/** - Write ordered array of structs from memory to the pros file */
		rewriteProsToFile(newAllPros, newProsNum, PROS_FNAME);
	}

	return -1;
}

int deletePro(professional *allPros, potential *allPts, unsigned int numRecords, char *toDeleteID,
		char *prosFile, char *ptsFile) {

	for (unsigned int i = 0; i < numRecords; i++) {
		if (strCompare(toDeleteID, (allPros + i)->id)) {
			(allPros + i)->toDelete = true;
		}
	}

	for (unsigned int i = 0; i < numRecords; i++) {
		if (strCompare(toDeleteID, (allPts + i)->id)) {
			(allPts + i)->toDelete = true;
		}
	}
	rewriteProsToFile(allPros, numRecords, prosFile);
	rewritePtsToFile(allPts, numRecords, ptsFile);

	return -1;
}

/**
 * Delete a professional and its potential identified by his ID inputted by the user.
 *
 * @param allPros Array of structs of all professionals registered.
 * @param allPts Array of structs of all potentials registered.
 * @param numRecords Number of professionals/potentials registered.
 * @return -1 for going back to the menu
 */
int requestProDeletion(professional *allPros, potential *allPts, unsigned int numRecords) {
	bool found = false;
	unsigned int proIndex = 0;
	unsigned int ptsIndex = 0;
	char toDeleteID[MAX_STRING_SIZE] = "";

	clearScr();
	printSectionName("Eliminazione professionista", false);

	printf("\nInserisci Codice Fiscale del professionista da eliminare: ");
	readString(toDeleteID, false, false, true);

	for (unsigned int i = 0; i < numRecords; i++) {
		if (strCompare(toDeleteID, (allPros + i)->id)) {
			found = true;
			proIndex = i;
		}

		for (unsigned int i = 0; i < numRecords; i++) {
			if (strCompare(toDeleteID, (allPts + i)->id)) {
				ptsIndex = i;
			}
		}
	}

	if (found) {
		// Show professional data before deletion confirmation (for user visual validation)
		showProData((allPros + proIndex), (allPts + ptsIndex), numRecords);
		
		setYellowColor();
		printf("\nSei sicuro di voler cancellare il professionista selezionato? (s/n): ");
		resetColor();

		if (askConfirm()) {
			deletePro(allPros, allPts, numRecords, toDeleteID, PROS_FNAME, PTS_FNAME);
			setGreenColor();
			printf("\nProfessionista eliminato!\n");
			resetColor();
		}
	} else {
		setRedColor();
		printf("\nNessun professionista trovato con l'ID inserito.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}
