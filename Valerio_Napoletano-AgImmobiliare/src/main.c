/**
 * @file main.c
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Entry point for starting the main menu
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "utils.h"
#include "datatypes.h"
#include "entities/pros.h"
#include "entities/buildings.h"
#include "entities/clients.h"

int main(void) {
	int result = 0;

	result += loadProFile();
	result += loadBuiFile();
	result += loadCliFile();

	if(result >= 0){
		mainMenu();
	}
	else{
		printf("\n------------------------ ATTENZIONE ------------------------");
		printf("\nErrore: I controlli iniziali sui file sono risultati in un errore.");
		printf("\nControlla il tuo file system e riprova.\n");
	}

	newLine();

	system("pause");
	return EXIT_SUCCESS;
}



