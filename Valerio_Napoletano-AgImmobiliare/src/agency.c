/**
 * @file agency.c
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Functions for handling agency's results.
 */

#include <stdio.h>
#include <stdlib.h>
// For parseDateInFile()
#include <time.h>

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"
#include "entities/buildings/files_bl.h"
#include "entities/buildings/show_bl.h"

/**
 * @brief Show how many buildings and which ones are available in a specific date interval.
 *
 * @param bl Array of structs of available buildings.
 * @param num_buildings Number of available buildings.
 * @return -1 for going back to the main menu
 */
int resultsAgency(building *bl, int num_buildings) {
	char date1[10];
	char date2[10];
	time_t reg_date1;
	time_t reg_date2;
	short int num_bl_found = 0;
	int tot_price = 0;
	bool error = false;
	bool b_stamp = true; //determines which category of buildings to print

	clearScr();
	printSectionName("Risultati agenzia", false);

	if (num_buildings != 0) {
		printf("\nInserisci primo intervallo di data (gg/mm/aaaa): ");
		readString(date1, false, false);
		reg_date1 = parseDateInFile(date1);

		printf("\nInserisci secondo intervallo di data (gg/mm/aaaa): ");
		readString(date2, false, false);
		reg_date2 = parseDateInFile(date2);

		newLine();

		if (reg_date1 < reg_date2) {
			setCyanColor();
			printf("--- IMMOBILI VENDUTI ---\n");
			newLine();
			resetColor();
			for (int count = 0; count < 2; count++) {
				for (int i = 0; i < num_buildings; i++) {
					if (bl[i].reg_date > reg_date1 && bl[i].reg_date < reg_date2 && bl[i].sold == b_stamp) {
						setCyanColor();
						printf("--- IMMOBILE %d ---", (bl + i)->id);
						resetColor();

						newLine();
						showBuildingData(bl + i);
						newLine();

						if (bl[i].sold == true) {
							tot_price += bl[i].price;
						}

						num_bl_found++;
					}
				}
				if (num_bl_found == 0 && !error) {
					setYellowColor();
					printf("Nessun immobile trovato con l'intervallo scelto.\n\n");
					resetColor();
				}
				b_stamp = false;
				num_bl_found = 0;

				if (count == 0) {
					setCyanColor();
					newLine();
					printf("--- IMMOBILI NON VENDUTI ---\n");
					newLine();
					resetColor();
				}
			}
			newLine();
			setCyanColor();
			printf("Ricavi Totali: ");
			resetColor();
			printf("%d euro\n", tot_price);
			newLine();

		} else {
			setRedColor();
			printf("E' stato inserito un intervallo errato.\n\n");
			error = true;
			resetColor();
		}

	} else {
		dbEmptyError();
	}
	pause();

	return -1;
}
