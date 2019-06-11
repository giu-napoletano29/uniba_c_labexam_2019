/**
 * @file misc_cl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "miscellaneous clients" functions.
 */

#ifndef ENTITIES_CLIENTS_MISC_CL_H_
#define ENTITIES_CLIENTS_MISC_CL_H_

int addClient(client *allClients, int numClients);
void saveLocalDate(client *cl);
bool checkIfUserExpired(time_t epochTime, char id[]);
void initClientsArray(client *cl, int size);
int deleteClient(client *allClients, int numClients);
void checkDuplicateClientID(client *cl, client *allClients, int numClients);

#endif /* ENTITIES_CLIENTS_MISC_CL_H_ */
