/**
 * @file agency.c
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Functions for handling agency's results.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /** For parseDateInFile() */

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"
#include "entities/buildings/files_bl.h"
#include "entities/buildings/show_bl.h"

/**
 * Show how many buildings and which ones are available in a specific date interval.
 *
 * @param bl Array of structs of available buildings.
 * @param n_bui Number of available buildings.
 * @return -1 for going back to the main menu
 */
int resultAg(building *bl, int n_bui) {
	char date1[10];
	char date2[10];
	time_t reg_date1;
	time_t reg_date2;
	short int num_bl_found = 0;
	bool error = false;

	clearScr();
	printf("\nInserisci primo intervallo di data (gg/mm/aaaa): ");
	readString(date1, false);
	reg_date1 = parseDateInFile(date1);

	printf("\nInserisci secondo intervallo di data (gg/mm/aaaa): ");
	readString(date2, false);
	reg_date2 = parseDateInFile(date2);

	newLine();

	if (reg_date1 < reg_date2) {
		for (int i = 0; i < n_bui; i++) {
			if (bl[i].reg_date > reg_date1 && bl[i].reg_date < reg_date2) {
				setCyanColor();
				printf("--- IMMOBILE %s ---", (bl + i)->id);
				resetColor();

				newLine();
				showBuildingData(bl + i);
				newLine();

				num_bl_found++;
			}
		}
	} else {
		setRedColor();
		printf("E' stato inserito un intervallo errato.\n\n");
		error = true;
		resetColor();
	}

	if (num_bl_found == 0 && !error) {
		setYellowColor();
		printf("Nessun immobile trovato con l'intervallo scelto.\n\n");
		resetColor();
	}
	pause();

	return -1;
}
