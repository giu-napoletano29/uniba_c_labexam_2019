/**
 * @file tests_cl.h
 * @author Saverio Valerio
 * @date 12 June 2019
 * @brief Header file with prototypes of the functions that made up the "clients" CUnit test suite
 */

#ifndef ENTITIES_CLIENTS_TESTS_CL_H_
#define ENTITIES_CLIENTS_TESTS_CL_H_

int initSuiteClients();
int cleanSuiteClients();
void testClientsFileParse();
void testClientDeletion();

#endif /* ENTITIES_CLIENTS_TESTS_CL_H_ */
