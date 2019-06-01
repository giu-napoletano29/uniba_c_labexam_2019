/**
 * @file files_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the clients' file management functions.
 */

#ifndef ENTITIES_BUILDINGS_FILES_BL_H_
#define ENTITIES_BUILDINGS_FILES_BL_H_

int loadBuildingsFile(building *bl);
void readBuildingsFile(FILE *filePtr, building *cl);
int searchBuilding(building *allBuildings, int num_buildings);
int getBuildingsNumber();
int rewriteBuildingsToFile(building *bl, int rows);
int checkDuplicateBuildings(building *bl, int rows);

#endif /* ENTITIES_BUILDINGS_FILES_BL_H_ */
