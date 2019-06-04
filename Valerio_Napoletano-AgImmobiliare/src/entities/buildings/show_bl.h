/**
 * @file show_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "show buildings" functions.
 */

#ifndef ENTITIES_BUILDINGS_SHOW_BL_H_
#define ENTITIES_BUILDINGS_SHOW_BL_H_

void showBuildingType();
void showBuildingData(building *bl);
int showAllBuildings(building *bl, int num_buildings);
void printBuildingChoices();

#endif /* ENTITIES_BUILDINGS_SHOW_BL_H_ */
