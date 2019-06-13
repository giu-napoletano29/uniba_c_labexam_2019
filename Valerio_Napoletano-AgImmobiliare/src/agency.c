/**
 * @file agency.c
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Functions for handling agency's results.
 */

#include <stdio.h>
#include <stdlib.h>
// For parseDate()
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
 * @param numBuildings Number of available buildings.
 * @return -1 for going back to the main menu
 */
int resultsAgency(building *bl, int numBuildings) {
	char startDateIntervalStr[10] = "";
	char endDateIntervalStr[10] = "";
	
	time_t startDateInterval = 0;
	time_t endDateInterval = 0;
	
	short int numBuildingsFound = 0;
	int totPrice = 0;
	bool error = false;

	clearScr();
	printSectionName("Risultati agenzia", false);

	if (numBuildings != 0) {
		printf("\nInserisci primo intervallo di data (gg/mm/aaaa): ");
		readString(startDateIntervalStr, false, false);
		startDateInterval = parseDate(startDateIntervalStr);

		printf("\nInserisci secondo intervallo di data (gg/mm/aaaa): ");
		readString(endDateIntervalStr, false, false);
		endDateInterval = parseDate(endDateIntervalStr);

		if (startDateInterval < endDateInterval) {
			setYellowColor();
			puts("\n--- I dati sono relativi al periodo scelto ---");
			
			// NOT SOLD HISTOGRAM
			setRedColor();
			printf("\nNON VENDUTI: \t|");
			for (int i = 0; i < numBuildings; i++) {
				if ((bl + i)->regDate >= startDateInterval && (bl + i)->regDate <= endDateInterval &&  (bl + i)->soldOn == 0) {
					printf("=");
					numBuildingsFound++;
				}
			}			
			printf("|\n %d", numBuildingsFound);
			resetColor();

			// SOLD HISTOGRAM
			numBuildingsFound = 0;
			newLine();
			setGreenColor();
			printf("\nVENDUTI: \t|");
			for (int i = 0; i < numBuildings; i++) {
				if ((bl + i)->soldOn >= startDateInterval && (bl + i)->soldOn <= endDateInterval) {
					printf("=");
					numBuildingsFound++;
					totPrice += bl[i].price;
				}
			}
			printf("|\n %d", numBuildingsFound);
			resetColor();
			
			// TOTAL PROFIT
			numBuildingsFound = 0;
			newLine();
			setCyanColor();
			printf("\nRicavi totali relativi al periodo: ");
			resetColor();
			printf("%d euro\n", totPrice);

			printf("\nVuoi visualizzare la lista degli immobili venduti? (s/n): ");
			if (askConfirm()) {
				for (int i = 0; i < numBuildings; i++) {
					if ((bl + i)->soldOn >= startDateInterval && (bl + i)->soldOn <= endDateInterval) {
						showBuildingData(bl + i);
						numBuildingsFound++;
					}
				}
				if (numBuildingsFound == 0 && !error) {
					setYellowColor();
					printf("Nessun immobile trovato con l'intervallo scelto.\n\n");
					resetColor();
				}
				numBuildingsFound = 0;
			}
		} else {
			setRedColor();
			printf("\nE' stato inserito un intervallo di data non valido.\n");
			error = true;
			resetColor();
		}

	} else {
		dbEmptyError();
	}
	newLine();
	pause();

	return -1;
}
