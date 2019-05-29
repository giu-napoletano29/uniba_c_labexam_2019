/*
 * clients_show.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_SHOW_CL_H_
#define ENTITIES_CLIENTS_SHOW_CL_H_

// Functions for showing data to the user
void showClientType();
void showClientData(client *cl);
int showAllClients(client *cl, int num_clients);

#endif /* ENTITIES_CLIENTS_SHOW_CL_H_ */
