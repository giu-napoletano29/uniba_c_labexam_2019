/*
 * clients_req.h
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_REQ_H_
#define ENTITIES_CLIENTS_REQ_H_

#include "../../datatypes.h"

// Functions for asking data to the user
void reqID(clients *client);
void reqName(clients *client);
void reqSurname(clients *client);
void reqType(clients *client);
void reqCompanyName(clients *client);
void reqBudget(clients *client);
void reqPropertyType(clients *client);

#endif /* ENTITIES_CLIENTS_REQ_H_ */
