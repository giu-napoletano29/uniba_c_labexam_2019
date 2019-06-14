/**
 * @file misc_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "miscellaneous buildings" functions.
 */
#ifndef ENTITIES_BUILDINGS_MISC_BL_H_
#define ENTITIES_BUILDINGS_MISC_BL_H_

void initBuildingsArray(building *bl, unsigned int size);
int addBuilding(building *allBuildings, unsigned int numBuildings);
int requestBuildingDeletion(building *allBuildings, unsigned int numBuildings);
int deleteBuilding(building *allBuildings, unsigned int numBuildings, unsigned int toDeleteID, char *filename);
int sellBuilding(building *allBuildings, unsigned int numBuildings);
int editBuilding(building *allBuildings, unsigned int numBuildings);

void checkDuplicateBuildingID(building *bl, building *allBuildings, unsigned int numBuildings);

#endif /* ENTITIES_BUILDINGS_MISC_BL_H_ */
