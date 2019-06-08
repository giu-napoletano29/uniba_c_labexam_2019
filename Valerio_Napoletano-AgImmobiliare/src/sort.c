/**
 * @file sort.c
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Sorting functions (with Bubble Sort) in alphabetical order by surname.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "datatypes.h"
#include "file_utils.h"
#include "utils.h"

/**
 * @brief Sort in alphabetical order the professional array of structs by surname.
 *
 * @param pr Array of structs, professional data type
 * @param rows Numbers of records in the "pr" array of structs.
 */
void sortPros(professional *pr, int rows) {
	professional cmp;
	int indexMin = 0;

	for (int j = 0; j < rows - 1; j++) {
		indexMin = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp((pr + i)->surname, (pr + indexMin)->surname) < 0) {
				indexMin = i;
			}
		}	// Element are moved at the end of the comparison process to avoid useless operation
		cmp.buildingsSold = (pr + j)->buildingsSold;
		(pr + j)->buildingsSold = (pr + indexMin)->buildingsSold;
		(pr + indexMin)->buildingsSold = cmp.buildingsSold;

		cmp.regDate = (pr + j)->regDate;
		(pr + j)->regDate = (pr + indexMin)->regDate;
		(pr + indexMin)->regDate = cmp.regDate;

		strcpy(cmp.name, (pr + j)->name);
		strcpy((pr + j)->name, (pr + indexMin)->name);
		strcpy((pr + indexMin)->name, cmp.name);

		strcpy(cmp.id, (pr + j)->id);
		strcpy((pr + j)->id, (pr + indexMin)->id);
		strcpy((pr + indexMin)->id, cmp.id);

		strcpy(cmp.surname, (pr + j)->surname);
		strcpy((pr + j)->surname, (pr + indexMin)->surname);
		strcpy((pr + indexMin)->surname, cmp.surname);

		strcpy(cmp.area, (pr + j)->area);
		strcpy((pr + j)->area, (pr + indexMin)->area);
		strcpy((pr + indexMin)->area, cmp.area);

		strcpy(cmp.phone, (pr + j)->phone);
		strcpy((pr + j)->phone, (pr + indexMin)->phone);
		strcpy((pr + indexMin)->phone, cmp.phone);

		strcpy(cmp.email, (pr + j)->email);
		strcpy((pr + j)->email, (pr + indexMin)->email);
		strcpy((pr + indexMin)->email, cmp.email);
	}
}

/**
 * @brief Sort in alphabetical order the client array of structs by surname.
 *
 * @param cl Array of structs, client data type
 * @param rows Numbers of records in the "cl" array of structs.
 */
void sortClients(client *cl, int rows) {
	client cmp;
	int indexMin = 0;

	for (int j = 0; j < rows - 1; j++) {
		indexMin = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp((cl + i)->surname, (cl + indexMin)->surname) < 0) {
				indexMin = i;
			}
		}	// Element are moved at the end of the comparison process to avoid useless operation
		cmp.budget = (cl + j)->budget;
		(cl + j)->budget = (cl + indexMin)->budget;
		(cl + indexMin)->budget = cmp.budget;

		cmp.clType = (cl + j)->clType;
		(cl + j)->clType = (cl + indexMin)->clType;
		(cl + indexMin)->clType = cmp.clType;

		cmp.toDelete = (cl + j)->toDelete;
		(cl + j)->toDelete = (cl + indexMin)->toDelete;
		(cl + indexMin)->toDelete = cmp.toDelete;

		cmp.buildingType = (cl + j)->buildingType;
		(cl + j)->buildingType = (cl + indexMin)->buildingType;
		(cl + indexMin)->buildingType = cmp.buildingType;

		cmp.regDate = (cl + j)->regDate;
		(cl + j)->regDate = (cl + indexMin)->regDate;
		(cl + indexMin)->regDate = cmp.regDate;

		strcpy(cmp.name, (cl + j)->name);
		strcpy((cl + j)->name, (cl + indexMin)->name);
		strcpy((cl + indexMin)->name, cmp.name);

		strcpy(cmp.id, (cl + j)->id);
		strcpy((cl + j)->id, (cl + indexMin)->id);
		strcpy((cl + indexMin)->id, cmp.id);

		strcpy(cmp.surname, (cl + j)->surname);
		strcpy((cl + j)->surname, (cl + indexMin)->surname);
		strcpy((cl + indexMin)->surname, cmp.surname);

		strcpy(cmp.companyName, (cl + j)->companyName);
		strcpy((cl + j)->companyName, (cl + indexMin)->companyName);
		strcpy((cl + indexMin)->companyName, cmp.companyName);
	}
}

/**
 * @brief Sort in alphabetical order the professional array of structs by owner name.
 *
 * @param bl Array of structs, building data type
 * @param rows Numbers of records in the "bl" array of structs.
 */
void sortBuildings(building *bl, int rows) {
	building cmp;
	int indexMin = 0;

	for (int j = 0; j < rows - 1; j++) {
		indexMin = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp((bl + i)->owner, (bl + indexMin)->owner) < 0) {
				indexMin = i;
			}
		}
		cmp.civic = (bl + j)->civic;
		(bl + j)->civic = (bl + indexMin)->civic;
		(bl + indexMin)->civic = cmp.civic;

		cmp.builType = (bl + j)->builType;
		(bl + j)->builType = (bl + indexMin)->builType;
		(bl + indexMin)->builType = cmp.builType;

		cmp.price = (bl + j)->price;
		(bl + j)->price = (bl + indexMin)->price;
		(bl + indexMin)->price = cmp.price;

		cmp.regDate = (bl + j)->regDate;
		(bl + j)->regDate = (bl + indexMin)->regDate;
		(bl + indexMin)->regDate = cmp.regDate;

		strcpy(cmp.city, (bl + j)->city);
		strcpy((bl + j)->city, (bl + indexMin)->city);
		strcpy((bl + indexMin)->city, cmp.city);

		cmp.id = (bl + j)->id;
		(bl + j)->id = (bl + indexMin)->id;
		(bl + indexMin)->id = cmp.id;

		strcpy(cmp.owner, (bl + j)->owner);
		strcpy((bl + j)->owner, (bl + indexMin)->owner);
		strcpy((bl + indexMin)->owner, cmp.owner);

		strcpy(cmp.phone, (bl + j)->phone);
		strcpy((bl + j)->phone, (bl + indexMin)->phone);
		strcpy((bl + indexMin)->phone, cmp.phone);

		strcpy(cmp.province, (bl + j)->province);
		strcpy((bl + j)->province, (bl + indexMin)->province);
		strcpy((bl + indexMin)->province, cmp.province);

		strcpy(cmp.street, (bl + j)->street);
		strcpy((bl + j)->street, (bl + indexMin)->street);
		strcpy((bl + indexMin)->street, cmp.street);
      
		cmp.soldOn = (bl + j)->soldOn;
		(bl + j)->soldOn = (bl + indexMin)->soldOn;
		(bl + indexMin)->soldOn = cmp.soldOn;
	}
}
