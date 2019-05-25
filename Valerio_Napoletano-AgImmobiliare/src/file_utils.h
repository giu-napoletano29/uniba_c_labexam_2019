/*
 * fileutils.h
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <stdio.h>
#include <stdbool.h>

#include "datatypes.h"

int checkFile(FILE *filePtr);
int countRows(FILE *filePtr);
void copyFile(FILE *fp_from, FILE *fp_to, int choice);
time_t parseDateInFile(char token[STRING_SIZE]);

#endif /* FILE_UTILS_H_ */
