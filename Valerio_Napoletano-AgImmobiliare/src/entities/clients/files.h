/*
 * clients_files.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_FILES_H_
#define ENTITIES_CLIENTS_FILES_H_

int loadClientFile();
void readClientFile(FILE *filePtr, clients *cl);
int saveClientToFile(clients *cl);

#endif /* ENTITIES_CLIENTS_FILES_H_ */
