/*
 * agency.c
 *
 *  Created on: 25 mag 2019
 *      Author: Giuseppe
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /** For parseDateInFile() */

#include "utils.h"
#include "file_utils.h"
#include "datatypes.h"
#include "entities/buildings/files_bl.h"
#include "entities/buildings/show_bl.h"

int resultAg(building *bl, int n_bui) {
	char date1[10];
	char date2[10];
	time_t reg_date1;
	time_t reg_date2;

	printf("\nInserisci primo intervallo di data: ");
	scanf("%s", date1);
	reg_date1 = parseDateInFile(date1);

	printf("\nInserisci secondo intervallo di data: ");
	scanf("%s", date2);
	reg_date2 = parseDateInFile(date2);

	if (reg_date1 < reg_date2) {
		for (int i = 0; i < n_bui; i++) {
			if (bl[i].reg_date > reg_date1 && bl[i].reg_date < reg_date2) {
				/*printf("\nEdificio: %s %s - %ld", bl[i].id, bl[i].owner, bl[i].reg_date);
				 printf("%s", asctime(gmtime(&bl[i].reg_date)));*/
				showBuildingData(bl + i);
			}
		}
	} else {
		printf("\nE' stato inserito un intervallo errato.\n");
	}
	pause();

	return -1;
}
