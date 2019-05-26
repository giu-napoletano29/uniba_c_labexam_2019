/*
 * clients_files.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_FILES_H_
#define ENTITIES_CLIENTS_FILES_H_

int loadBuildingsFile(building *bl);
void readBuildingsFile(FILE *filePtr, building *cl);
void searchBuilding(building *bl, int n_bui);
int getbuildingsNumber();
int rewritebuildingsToFile(building *bl, int rows);

#endif /* ENTITIES_CLIENTS_FILES_H_ */
