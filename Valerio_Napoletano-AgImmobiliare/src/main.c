/**
 * @file main.c
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Entry point for starting the main menu
 */

#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "utils.h"
#include "datatypes.h"

#include "tests.h"

int main(void) {
	bool runTestsAtStartup = true;

	if (runTestsAtStartup) {
		startTests();
		// ANSI escape codes not supported in CUnit output, falling back to original
		newLine();
		system("pause");
	}
	
	mainMenu();

	return 0;
}

