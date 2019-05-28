/*
 * pros/files.h
 *
 *  Created on: 23 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_PROS_FILES_H_
#define ENTITIES_PROS_FILES_H_

int loadProsFile(professional *pr);
int getProfessionalsNumber();
int rewriteProfessionalsToFile(professional *pr, int rows);
void readProsFile(FILE *filePtr, professional *pr);
void readPotFile(FILE *fp_pot, potential *pr, char id[], int rows);
void findPot(char id[], potential *pr, int rows);
int loadPotFile(char id[]);
int checkDuplicatePro(professional *pr, int rows);

#endif /* ENTITIES_PROS_FILES_H_ */
