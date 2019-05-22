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
int loadCliFile();
void readFileCli(FILE *fp_cli, clients *p);

// Functions for asking data to the user
void reqID(clients *client);
void reqName(clients *client);
void reqSurname(clients *client);
void reqType(clients *client);
void reqCompanyName(clients *client);
void reqBudget(clients *client);
void reqPropertyType(clients *client);

// Get local system date and save in the related struct (only for Windows)
void saveLocalDate(clients *client);

// Functions for showing data to the user
void showClientType();
void showPropertyType();
void showClientData(clients *cl);
int showAllClients();

// Functions for modifying data
int deleteClient();

#endif /* CLIENTS_H_ */
