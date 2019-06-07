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
void initPotentialsArray(potential *po, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(po[i].id, "");
		strcpy(po[i].content, "");
	}
}

/**
 * @brief Initialize an array of structs of professionals.
 *
 * @param pro "Professional" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initProsArray(professional *pro, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(pro[i].id, "");
		strcpy(pro[i].name, "");
		strcpy(pro[i].surname, "");
		strcpy(pro[i].area, "");
		strcpy(pro[i].phone, "");
		strcpy(pro[i].email, "");
		pro[i].reg_date = 0;
		pro[i].buildings_sold = 0;
	}
}

/**
 * @brief Get current system date and save the UNIX Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param pr "professional" type struct
 */
void saveLocalDatePro(professional *pr) {
	time_t timeRightNow;

	// time function returns the current Epoch time (time_t)
	pr->reg_date = time(&timeRightNow);
}

/**
 * @brief Append a professional to its file.
 * Initializes a "professional" struct and calls the "req" functions for filling the latter.
 *
 * allProfessionals and num_pros parameters are needed
 * for calling sortPros() and rewriteProsToFile()
 *
 * @param allPros Array of structs (professional type)
 * @param allPts Array of structs (potential type)
 * @param num_records Number of items professionals/potentials saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int addPro(professional *allPros, potential *allPts, int num_records) {
	professional pr = { "", "", "", "", "", "", 0, 0, false };
	potential pt = { "", "" };
	int newProsNum = 0;
	int newPtsNum = 0;

	clearScr();
	printSectionName("Aggiunta professionista", false);
	newLine();

	reqProCF(&pr);

	reqProName(&pr);

	reqProSurname(&pr);

	reqProArea(&pr);

	reqProPhone(&pr);

	reqProEmail(&pr);

	reqProSoldBuildings(&pr);

	reqProPotential(&pr, &pt);

	saveLocalDatePro(&pr);

	appendProToFile(&pr);

	appendPtsToFile(&pt);

	// --- PROFESSIONALS ---

	/** - Sort professionls in the memory */
	sortPros(allPros, num_records);

	/** - Re-declare and re-initialize the array of structs with the newly created pro */
	newProsNum = countFileRows("professionals");
	professional newAllPros[newProsNum];
	initProsArray(newAllPros, newProsNum);

	/** - Load pros file and stores the parsed data in the memory. */
	loadProsFile(newAllPros);

	/** - Rewrite ordered array of structs from memory to the pros file */
	rewriteProsToFile(newAllPros, newProsNum);

	// --- POTENTIALS ---

	/** - Re-declare and re-initialize the array of structs with the newly created potentials */
	newPtsNum = countFileRows("pros_potential");
	potential newAllPts[newPtsNum];
	initPotentialsArray(newAllPts, newPtsNum);

	/** - Load potentials file and stores the parsed data in the memory. */
	loadPotentialsFile(newAllPts);

	/** - Rewrite ordered array of structs from memory to the pros file */
	rewritePtsToFile(newAllPts, newPtsNum);

	return -1;
}

/**
 * Delete a professional and its potential identified by his ID inputted by the user.
 *
 * @param allPros Array of structs of all professionals registered.
 * @param allPts Array of structs of all potentials registered.
 * @param num_records Number of professionals/potentials registered.
 * @return -1 for going back to the menu
 */
int deletePro(professional *allPros, potential *allPts, int num_records) {
	bool found = false;

	clearScr();
	printSectionName("Eliminazione professionista", false);

	char toDeleteID[MAX_STRING_SIZE];
	printf("\nInserisci Codice Fiscale del professionista da eliminare: ");
	readString(toDeleteID, false, false);

	for (int i = 0; i < num_records; i++) {
		// Set the "toDelete" flag on true of the chosen professional
		if (strCompare(toDeleteID, (allPros + i)->id)) {
			(allPros + i)->toDelete = true;
			found = true;
		}
	}

	if (found) {
		// Set the "toDelete" flag on true of the professional "potential"
		for (int i = 0; i < num_records; i++) {
			if (strCompare(toDeleteID, (allPts + i)->id)) {
				(allPts + i)->toDelete = true;
			}
		}

		rewriteProsToFile(allPros, num_records);
		rewritePtsToFile(allPts, num_records);

		setGreenColor();
		printf("\nProfessionista eliminato!\n");
		resetColor();
	} else {
		setRedColor();
		printf("\nNessun professionista trovato con l'ID inserito.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}
