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
#include "entities/properties.h"

int main(void) {
	int result = 0;

	result += loadProFile();
	result += loadBuiFile();

	mainMenu();

	system("pause");
	return EXIT_SUCCESS;
}



