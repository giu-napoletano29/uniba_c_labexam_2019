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
	short int result = 0;

	result += loadProFile();
	result += loadBuiFile();
	result += loadCliFile();

	mainMenu();

	system("pause");

	return EXIT_SUCCESS;
}

