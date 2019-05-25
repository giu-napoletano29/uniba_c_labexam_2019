/*
 * clients_files.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_FILES_H_
#define ENTITIES_CLIENTS_FILES_H_

int loadClientFile(clients *cl);
void parseClientFile(FILE *filePtr, clients *cl);
int rewriteClientsToFile(clients *cl, int rows);
int appendClientToFile(clients *cl);

int getClientsNumber();

#endif /* ENTITIES_CLIENTS_FILES_H_ */
