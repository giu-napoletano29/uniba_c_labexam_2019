/*
 * clients_req.h
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef ENTITIES_CLIENTS_REQ_CL_H_
#define ENTITIES_CLIENTS_REQ_CL_H_

#include "../../datatypes.h"

// Functions for asking data to the user
void reqID(client *cl);
void reqCF(client *cl);
void reqPIVA(client *cl);
void reqName(client *cl);
void reqSurname(client *cl);
void reqType(client *cl);
void reqCompanyName(client *cl);
void reqBudget(client *cl);
void reqPropertyType(client *cl);

#endif /* ENTITIES_CLIENTS_REQ_CL_H_ */
