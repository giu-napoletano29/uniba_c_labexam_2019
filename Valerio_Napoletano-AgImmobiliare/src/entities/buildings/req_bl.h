/**
 * @file req_bl.h
 * @author Saverio Valerio
 * @date 2 June 2019
 * @brief Header file containing prototype related to the "request buildings' data" functions.
 */

#ifndef ENTITIES_BUILDINGS_REQ_BL_H_
#define ENTITIES_BUILDINGS_REQ_BL_H_

void genBuildingID(building *bl);
void reqBuildingStreet(building *bl);
void reqBuildingCity(building *bl);
void reqBuildingProvince(building *bl);
void reqBuildingPrice(building *bl);
void reqBuildingOwner(building *bl);
void reqBuildingPhone(building *bl);
void reqBuildingType(building *bl);

#endif /* ENTITIES_BUILDINGS_REQ_BL_H_ */
