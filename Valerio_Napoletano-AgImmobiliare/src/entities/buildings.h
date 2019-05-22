/*
 * buildings.h
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef BUILDINGS_H_
#define BUILDINGS_H_

int addBuilding();
int editBuilding();
int removeBuilding();

void infoBuilding(FILE *fp_build);

int loadBuiFile();
void readFileBui(FILE *fp_build, property *p);

#endif /* BUILDINGS_H_ */
