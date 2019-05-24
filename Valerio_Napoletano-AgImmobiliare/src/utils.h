/*
 * utils.h
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdbool.h>
#include "datatypes.h"

void newLine();
void clearScr();

// Utils functions used by readString and readInteger for input checks
bool isNumber(char *str);
bool isChar(char *str);

void printFormattedDate(time_t epochTime);

str_result readString(bool numCheck);
int_result readInteger();
