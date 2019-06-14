/**
 * @file misc_cl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "miscellaneous clients" functions.
 */

#ifndef ENTITIES_CLIENTS_MISC_CL_H_
#define ENTITIES_CLIENTS_MISC_CL_H_

int addClient(client *allClients, unsigned int numClients);
void saveLocalDate(client *cl);
bool checkIfUserExpired(time_t epochTime, char id[]);
void initClientsArray(client *cl, unsigned int size);
int requestClientDeletion(client *allClients, unsigned int numClients);
int deleteClient(client *allClients, unsigned int numClients, char *toDeleteID, char *filename);
void checkDuplicateClientID(client *cl, client *allClients, unsigned int numClients);

#endif /* ENTITIES_CLIENTS_MISC_CL_H_ */
