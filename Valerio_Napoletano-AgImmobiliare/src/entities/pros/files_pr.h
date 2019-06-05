/**
 * @file files_pr.h
 * @author Saverio Valerio
 * @date 23 May 2019
 * @brief Header file containing prototypes related to the pros' file management functions.
 */

#ifndef ENTITIES_PROS_FILES_PR_H_
#define ENTITIES_PROS_FILES_PR_H_

#include "../../datatypes.h"

int loadProsFile(professional *pr);
int getProsNumber();
void readProsFile(FILE *filePtr, professional *pr);
void parsePotentialsFile(FILE *fp_pot, potential *pr, char id[], int rows);
void findPotential(char id[], potential *pr, int rows);
void loadPotFile(char id[]);
void rewriteProsToFile(professional *pr, int rows);
int checkDuplicatePros(professional *pr, int rows);

#endif /* ENTITIES_PROS_FILES_PR_H_ */
