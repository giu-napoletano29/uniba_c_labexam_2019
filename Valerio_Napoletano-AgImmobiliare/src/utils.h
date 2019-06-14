/**
 * @file utils.h
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Header file containing prototypes related to the "utils" functions.
 */

#include <stdbool.h>
#include "datatypes.h"

void newLine();
void clearScr();

bool isNumber(char *str);
bool isChar(char *str);

void printFormattedDate(time_t epochTime);
void printSectionName(char *string, bool isHome);
time_t parseDate(char string[MAX_STRING_SIZE], bool errorCheck);

void convertToUpperCase(char *s);
bool strCompare(char *from, char *to);
bool askConfirm();

int readString(char *value, bool onlyAlpha, bool onlyNumbers, bool onlyAlphaNumbers);
int readInteger();
double readDouble();

void resetColor();
void setRedColor();
void setYellowColor();
void setGreenColor();
void setCyanColor();

void pause();
void notFoundError();

void setTitle(char *titleToSet);
void dbEmptyError();
