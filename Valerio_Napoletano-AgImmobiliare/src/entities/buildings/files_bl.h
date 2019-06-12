/**
 * @file files_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the clients' file management functions.
 */

#ifndef ENTITIES_BUILDINGS_FILES_BL_H_
#define ENTITIES_BUILDINGS_FILES_BL_H_

#include <stdio.h>

#include "../../datatypes.h"

int loadBuildingsFile(building *bl, char *filename);
void parseBuildingsFile(FILE *filePtr, building *cl);
int searchBuilding(building *allBuildings, int numBuildings);
int rewriteBuildingsToFile(building *bl, int rows);
int checkDuplicateBuildings(building *bl, int rows);
int appendBuildingToFile(building *bl, char *filename);

#endif /* ENTITIES_BUILDINGS_FILES_BL_H_ */
