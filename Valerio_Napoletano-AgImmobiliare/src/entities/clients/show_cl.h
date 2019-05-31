/**
 * @file show_cl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Header file containing prototypes related to the "show clients" functions.
 */

#ifndef ENTITIES_CLIENTS_SHOW_CL_H_
#define ENTITIES_CLIENTS_SHOW_CL_H_

void showClientType();
void showClientData(client *cl);
int showAllClients(client *cl, int num_clients);

#endif /* ENTITIES_CLIENTS_SHOW_CL_H_ */
