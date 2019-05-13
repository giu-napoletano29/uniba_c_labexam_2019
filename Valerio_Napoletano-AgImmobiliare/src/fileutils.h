/*
 * fileutils.h
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <stdio.h>

int checkFile(FILE *fp_build);
void infoBuild(FILE *fp_build);
int countRows(FILE *fp_build);
void copyFile(FILE *fp_from, FILE *fp_to, int choice);


#endif /* FILEUTILS_H_ */
