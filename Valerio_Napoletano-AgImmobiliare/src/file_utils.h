/**
 * @file file_utils.h
 * @author Giuseppe Napoletano
 * @date 13 May 2019
 * @brief Header file containing prototypes related to the "file_utils" functions.
 */

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <stdio.h>
#include <stdbool.h>

#include "datatypes.h"

bool checkFile(FILE *filePtr);
int countFileRows(char *name);
void copyFile(FILE *fp_from, FILE *fp_to, int choice);
time_t parseDate(char string[MAX_STRING_SIZE]);
void formattedDateToFile(FILE *filePtr, time_t *epochTime);

#endif /* FILE_UTILS_H_ */
