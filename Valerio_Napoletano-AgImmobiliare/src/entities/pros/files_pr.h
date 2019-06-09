/**
 * @file files_pr.h
 * @author Saverio Valerio
 * @date 23 May 2019
 * @brief Header file containing prototypes related to the pros' file management functions.
 */

#ifndef ENTITIES_PROS_FILES_PR_H_
#define ENTITIES_PROS_FILES_PR_H_

#include "../../datatypes.h"

int loadProsFile(professional *allPros);
void parseProsFile(FILE *filePtr, professional *pr);
int checkDuplicatePros(professional *allPros, potential *allPts, int rows);
int appendProToFile(professional *pr);
int rewriteProsToFile(professional *allPros, int rows);

#endif /* ENTITIES_PROS_FILES_PR_H_ */
