/*
 * properties.c
 *
 *  Created on: 11 mag 2019
 *      Author: Giuseppe Napoletano
 */

//Operazioni su immobili
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils.h"
#include "../file_utils.h"
#include "../datatypes.h"

void infoBuild(FILE *fp_build) {
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

void readFileBui(FILE *fp_build, property *pro) {
	char line[400];
	char *token;
	char *dtoken;
	char date[10];

	int field;
	int dfield = 0;
	// Professional nums counter
	int b_num = 0;

	while (fgets(line, sizeof line, fp_build) != NULL) /* read a line */
	{
		// Fields counter
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
			case 0:
				pro[b_num].id = atoi(token);
				break;
			case 1:
				strcpy(pro[b_num].name, token);
				break;
			case 2:
				strcpy(pro[b_num].locality, token);
				break;
			case 3:
				pro[b_num].price = atoi(token);
				break;
			case 4:
				strcpy(date, token);
				dfield = 0;
				dtoken = strtok(date, "/");

				while( dtoken != NULL ) {
					switch (dfield) {
					case 0:
						pro[b_num].reg_date.day = atoi(dtoken);
						break;
					case 1:
						pro[b_num].reg_date.month = atoi(dtoken);
						break;
					case 2:
						pro[b_num].reg_date.year = atoi(dtoken);
						break;
					}

				   dtoken = strtok(NULL, "/");

				   dfield++;
				}
				break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		printf("\n--- APPARTAMENTO %d ---\n", b_num + 1);
		printf("\nID: %d\n", pro[b_num].id);
		printf("\nNAME: %s\n", pro[b_num].name);
		printf("\nLOCALITY: %s\n", pro[b_num].locality);
		printf("\nPRICE: %d\n", pro[b_num].price);
		printf("\nDATE: %d/%d/%d\n", pro[b_num].reg_date.day, pro[b_num].reg_date.month, pro[b_num].reg_date.year);

		b_num++;

		newLine();
		system("pause");
	}
}

int loadBuiFile() {
	int rows = 0;
	int result = 0; //detects the failure or success of the function
	FILE *fp_build;
	fp_build = fopen("buildings.dat", "a+");
	checkFile(fp_build);
	if (fp_build != NULL) {
		rows = countRows(fp_build);
		rewind(fp_build);
		property p[rows];
		readFileBui(fp_build, p);
	}
	else{
		result = -1;
	}

	fclose(fp_build);
	return result;
}

int addBuild() {
	FILE *fp_build;
	fp_build = fopen("buildings.dat", "a+b");

	checkFile(fp_build);
	if (fp_build != NULL) {
		infoBuild(fp_build);
	}

	fclose(fp_build);

	return -1;
}
int editBuild() {
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen("buildings.dat", "rb");
	checkFile(fp_build);
	if (fp_build != NULL) {
		count = countRows(fp_build);
		fclose(fp_build);

		fp_build = fopen("buildings.dat", "rb");
		checkFile(fp_build);

		fp_temp = fopen("temp_build.dat", "w+b");
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

					fp_build = fopen("buildings.dat", "w+b");
					fp_temp = fopen("temp_build.dat", "rb");

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
		remove("temp_building.dat");
	}
	return -1;
}
int removeBuild() {
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen("buildings.dat", "rb");
	checkFile(fp_build);
	if (fp_build != NULL) {
		count = countRows(fp_build);
		fclose(fp_build);
		fp_build = fopen("buildings.dat", "rb");
		checkFile(fp_build);
		fp_temp = fopen("temp_build.dat", "w+b");
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
					fp_build = fopen("buildings.dat", "w+b");
					fp_temp = fopen("temp_build.dat", "rb");

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
	remove("temp_building.dat");

	return -1;
}
