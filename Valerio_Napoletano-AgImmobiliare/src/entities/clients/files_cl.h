/**
 * @file files_cl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the clients' file management functions.
 */

#ifndef ENTITIES_CLIENTS_FILES_CL_H_
#define ENTITIES_CLIENTS_FILES_CL_H_

int loadClientFile(client *cl);
void parseClientFile(FILE *filePtr, client *cl);
int rewriteClientsToFile(client *cl, int rows);
int appendClientToFile(client *cl);
int checkDuplicateClients(client *cl, int rows);

int getClientsNumber();

#endif /* ENTITIES_CLIENTS_FILES_CL_H_ */
