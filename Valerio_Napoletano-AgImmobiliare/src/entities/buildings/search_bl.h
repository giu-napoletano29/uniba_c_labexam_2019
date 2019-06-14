/**
 * @file search_bl.h
 * @author Saverio Valerio
 * @date 8 June 2019
 * @brief Header file containing prototypes related to the "search buildings" functions.
 */

#ifndef ENTITIES_BUILDINGS_SEARCH_BL_H_
#define ENTITIES_BUILDINGS_SEARCH_BL_H_

void searchBuildingsForPrice(building *allBuildings, unsigned int numBuildings);
void searchBuildingsForCity(building *allBuildings, unsigned int numBuildings);
void searchBuildingsCtrType(building *allBuildings, unsigned int numBuildings);
void searchBuildingsByType(building *allBuildings, unsigned int numBuildings);
int searchBuilding(building *allBuildings, unsigned int numBuildings);

#endif /* ENTITIES_BUILDINGS_SEARCH_BL_H_ */
