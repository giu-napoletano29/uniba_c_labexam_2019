/*
 * pros.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"
#include "../fileutils.h"

int loadProFile() {
	int rows = 0;
	FILE *fp_pro;
	fp_pro = fopen("professionals.dat", "rb");
	checkFile(fp_pro);
	if (fp_pro != NULL) {
		rows = countRows(fp_pro);
		rewind(fp_pro);
		professionals p[rows];
		readFilePro(fp_pro, rows, p);
	}

	fclose(fp_pro);
	return -1;
}

int updProFile() {
	FILE *fp_pro;
	fp_pro = fopen("professionals.dat", "ab+");

	checkFile(fp_pro);
	if (fp_pro != NULL) {
		infoPro(fp_pro);
	}

	fclose(fp_pro);
	return -1;
}

int addPro() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Scelta non valida, per favore riprova. \n");
		}

		puts("--- PROFESSIONISTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Carica nuovo file professionisti");
		puts("2. Aggiorna file esistente");
		puts("3. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadProFile();
			break;
		case 2:
			choice = updProFile();
			break;
		case 3:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -2;
			error = false;
			break;
		default:
			error = true;
			break;
		}

	} while (error == true);
	return choice;
}

int editPro() {

	return -1;
}
