/*
 * utils.c
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>

// Just print a new line to the console
void newLine() {
	printf("\n");
}

// Clear the console emulator screen (multiplatform)
void clearScr() {
	// Macros from https://sourceforge.net/p/predef/wiki/OperatingSystems/`
	// "defined": http://port70.net/~nsz/c/c11/n1570.html#6.10.1p1

	#if defined(_WIN32)
		// Windows
		system("cls");
	#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
		// Unix based systems (GNU/Linux, macOS, etc..)
		system("clear");
	#endif
}
