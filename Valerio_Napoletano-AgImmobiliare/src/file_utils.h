/*
 * fileutils.h
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <stdio.h>
#include "datatypes.h"

int checkFile(FILE *fp_build);
int countRows(FILE *fp_build);
void copyFile(FILE *fp_from, FILE *fp_to, int choice);

#endif /* FILE_UTILS_H_ */
