/*
 * utils.h
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdbool.h>

void newLine();
void clearScr();

bool isNumber(char *str);
bool readString(char *buffer, bool numCheck);

bool isChar(char *str);
bool readInteger(int *result_num, bool charCheck);
