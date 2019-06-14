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
int showAllBuildings(building *bl, unsigned int numBuildings);
void printBuildingChoices();
void showContractType(unsigned short int type);
void printContractChoices();

#endif /* ENTITIES_BUILDINGS_SHOW_BL_H_ */
