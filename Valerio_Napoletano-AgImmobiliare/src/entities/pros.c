/*
 * pros.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */
#include <stdio.h>
#include <stdbool.h>

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"
#include "../fileutils.h"

int addPro(){
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
			//choice = loadProFile();
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

int updProFile(){
	FILE *fp_build;
	fp_build = fopen ("professionals.dat", "a+b");

    checkFile(fp_build);
    if (fp_build!=NULL){
    	infoPro(fp_build);
    }

    fclose(fp_build);
	return -1;
}

int loadProFile(){


	return -1;
}
