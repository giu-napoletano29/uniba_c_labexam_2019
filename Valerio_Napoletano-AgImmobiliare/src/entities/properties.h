/*
 * properties.h
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

//Operazioni su immobili
int addBuild();
int editBuild();
int loadBuiFile();
void readFileBui(FILE *fp_build, professionals *p);
int removeBuild();

void infoBuild(FILE *fp_build);

#endif /* PROPERTIES_H_ */
