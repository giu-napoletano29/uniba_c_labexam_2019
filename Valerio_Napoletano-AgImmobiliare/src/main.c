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
<<<<<<< HEAD
#include "entities/buildings.h"
#include "entities/clients.h"
=======
#include "entities/properties.h"
>>>>>>> parent of e6ddbe1... Added read clients file at startup function

int main(void) {
	short int result = 0;

	result += loadProFile();
	result += loadBuiFile();

	mainMenu();

	system("pause");

	return EXIT_SUCCESS;
}

