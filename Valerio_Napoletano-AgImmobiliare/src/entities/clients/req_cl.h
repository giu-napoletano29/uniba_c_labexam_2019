/**
 * @file req_cl.h
 * @author Saverio Valerio
 * @date 11 May 2019
 * @brief Header file containing prototypes related to the "request clients' data" functions.
 */

#ifndef ENTITIES_CLIENTS_REQ_CL_H_
#define ENTITIES_CLIENTS_REQ_CL_H_

#include "../../datatypes.h"

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
