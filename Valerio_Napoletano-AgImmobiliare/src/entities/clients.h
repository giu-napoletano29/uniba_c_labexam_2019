/*
 * clients.h
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "../datatypes.h"

// "main" function
int addClient();

// Functions for asking data to the user
void reqName(clients *client);
void reqSurname(clients *client);
void reqType(clients *client);
void reqCompanyName(clients *client);
void reqBudget(clients *client);
void reqPropertyType(clients *client);

// Functions for showing data to the user
void showClientType();
void showPropertyType();
void showClientData(clients *cl);

#endif /* CLIENTS_H_ */
