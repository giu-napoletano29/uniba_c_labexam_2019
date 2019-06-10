/**
 * @file misc_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "miscellaneous buildings" functions.
 */
#ifndef ENTITIES_BUILDINGS_MISC_BL_H_
#define ENTITIES_BUILDINGS_MISC_BL_H_

void initBuildingsArray(building *bl, int size);
int addBuilding(building *allBuildings, int numBuildings);
int deleteBuilding(building *allBuildings, int numBuildings);
int sellBuilding(building *allBuildings, int numBuildings);
int editBuilding(building *allBuildings, int numBuildings);

void checkDuplicateIDbl(building *bl, building *allBuildings, int numBuildings);

#endif /* ENTITIES_BUILDINGS_MISC_BL_H_ */
