/*
 * clients_files.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_FILES_H_
#define ENTITIES_CLIENTS_FILES_H_

int loadClientFile(client *cl);
void parseClientFile(FILE *filePtr, client *cl);
int rewriteClientsToFile(client *cl, int rows);
int appendClientToFile(client *cl);
int checkDuplicateClients(client *cl, int rows);

int getClientsNumber();

#endif /* ENTITIES_CLIENTS_FILES_H_ */
