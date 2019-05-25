/*
 * clients_show.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_SHOW_H_
#define ENTITIES_CLIENTS_SHOW_H_

// Functions for showing data to the user
void showClientType();
void showClientData(clients *cl);
int showAllClients(clients *cl, int num_clients);

void checkIfUserExpired(time_t epochTime, char id[]);

#endif /* ENTITIES_CLIENTS_SHOW_H_ */
