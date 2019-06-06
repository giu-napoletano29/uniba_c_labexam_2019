/*
 * files_pts.h
 *
 *  Created on: 6 giu 2019
 *      Author: Saverio Valerio
 */


void findPotential(char id[], potential *pr, int num_profess);
void parsePotentialsFile(FILE *fp_pot, potential *pr, int rows);
int getPotsNumber();
void loadPotentialsFile(char id[]);
