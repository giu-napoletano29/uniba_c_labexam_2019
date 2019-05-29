/*
 * clients_misc.h
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_MISC_H_
#define ENTITIES_CLIENTS_MISC_H_

// "main" function
int addClient();

// Get local system date and save in the related struct (only for Windows)
void saveLocalDate(client *cl);

bool checkIfUserExpired(time_t epochTime, char id[]);

void initClientsArray(client *cl, int size);

#endif /* ENTITIES_CLIENTS_MISC_H_ */
