/*
 * buildings.c
 *
 *  Created on: 11 mag 2019
 *      Author: Giuseppe Napoletano
 */

#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
#include "../file_utils.h"
#include "../datatypes.h"

void infoBuilding(FILE *fp_build) {
	property p;
	//TODO: need to handle escape characters
	printf("Inserisci l'ID dell'immobile: \n");
	scanf("%d", &p.id);
	printf("Inserisci il nome dell'immobile: \n");
	scanf("%s", p.name);
	printf("Inserisci la localita': \n");
	scanf("%s", p.locality);
	printf("Inserisci il prezzo: \n");
	scanf("%d", &p.price);
	printf("Inserisci la data: \n");
	scanf("%hd %hd %hd", &p.reg_date.day, &p.reg_date.month, &p.reg_date.year);	//TODO: Inserire controllo data

	fprintf(fp_build, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality,
			p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);
}

int addBuilding() {
	FILE *fp_build;
	fp_build = fopen("buildings.csv", "a+b");

	checkFile(fp_build);
	if (fp_build != NULL) {
		infoBuilding(fp_build);
	}

	fclose(fp_build);

	return -1;
}
int editBuilding() {
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen("buildings.csv", "rb");
	checkFile(fp_build);
	if (fp_build != NULL) {
		count = countRows(fp_build);
		fclose(fp_build);

		fp_build = fopen("buildings.csv", "rb");
		checkFile(fp_build);

		fp_temp = fopen("temp_build.csv", "w+b");
		stop = checkFile(fp_temp);

		if (count > 0 && stop == 0) {
			do {
				newLine();
				printf("Inserisci il numero dell'immobile da modificare: \n");
				scanf("%d", &choice);

				if (choice <= count) {
					copyFile(fp_build, fp_temp, choice);

					fclose(fp_temp);
					fclose(fp_build);

					fp_build = fopen("buildings.csv", "w+b");
					fp_temp = fopen("temp_build.csv", "rb");

					copyFile(fp_temp, fp_build, 0);

					stop = 0;
				} else {
					printf("\nYou must enter a valid number.\n");
					stop = 1;
				}
			} while (stop == 1);
		} else {
			printf("\n---- WARNING ----");
			printf("\nNo data found.\n");
		}

		fclose(fp_temp);
		fclose(fp_build);
		remove("temp_building.csv");
	}
	return -1;
}
int removeBuilding() {
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen("buildings.csv", "rb");
	checkFile(fp_build);
	if (fp_build != NULL) {
		count = countRows(fp_build);
		fclose(fp_build);
		fp_build = fopen("buildings.csv", "rb");
		checkFile(fp_build);
		fp_temp = fopen("temp_build.csv", "w+b");
		stop = checkFile(fp_temp);
		//UNUSED
		//char line[400];
		if (count > 0 && stop == 0) {
			do {
				newLine();
				printf("Inserisci il numero dell'immobile da eliminare: \n");
				scanf("%d", &choice);
				if (choice <= count) {
					count = 0;
					copyFile(fp_build, fp_temp, -choice);

					fclose(fp_temp);
					fclose(fp_build);
					fp_build = fopen("buildings.csv", "w+b");
					fp_temp = fopen("temp_build.csv", "rb");

					copyFile(fp_temp, fp_build, 0);

					stop = 0;
				} else {
					printf("\nYou must enter a valid number.\n");
					stop = 1;
				}
			} while (stop == 1);
		}
	}
	fclose(fp_temp);
	fclose(fp_build);
	remove("temp_building.csv");

	return -1;
}
