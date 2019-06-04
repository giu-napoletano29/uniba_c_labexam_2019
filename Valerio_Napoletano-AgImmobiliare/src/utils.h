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
void convertToUpperCase(char *s);

int readString(char *value, bool onlyAlpha, bool onlyNumbers);
int readInteger();

bool strCompare(char *from, char *to);
bool askConfirm();

void resetColor();
void setRedColor();
void setYellowColor();
void setGreenColor();
void setCyanColor();
void setMagentaColor();

void pause();
void notFoundError();

void setTitle(char *titleToSet);
void dbEmptyError();
