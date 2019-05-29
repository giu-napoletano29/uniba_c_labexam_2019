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

void convertToUpperCase(char *s);

//Color functions
void resetColor();
void setRedColor();
void setYellowColor();
void setGreenColor();
void setCyanColor();
void setMagentaColor();

void pause();
void notFoundError();

void printSectionName(char *headerString);
bool strCompare(char *from, char *to);
bool askConfirm();
