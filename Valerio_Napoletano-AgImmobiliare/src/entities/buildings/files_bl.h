/*
 * buildings/files.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_BUILDINGS_FILES_BL_H_
#define ENTITIES_BUILDINGS_FILES_BL_H_

int loadBuildingsFile(building *bl);
void readBuildingsFile(FILE *filePtr, building *cl);
void searchBuilding(building *bl, int n_bui);
int getBuildingsNumber();
int rewriteBuildingsToFile(building *bl, int rows);
int checkDuplicateBuildings(building *bl, int rows);

#endif /* ENTITIES_BUILDINGS_FILES_BL_H_ */
