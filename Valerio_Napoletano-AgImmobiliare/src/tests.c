/**
 * @file tests.c
 * @author Saverio Valerio
 * @date 12 June 2019
 * @brief Main functions for running CUnit tests with the test registry and test methods declaration
 */

#include "CUnit/Basic.h"

#include "entities/clients/tests_cl.h"
#include "entities/buildings/tests_bl.h"

/**
 * @brief Runs automatically the CUnit tests and reports to stdout.
 * 
 * - Initializes the CUnit test registry
 * - Declares the various available test methods
 * - Runs the test with verbosing
 * - Cleans up the test registry
 * @return
 */
int startTests() {
	CU_initialize_registry();
	
	CU_pSuite pSuiteClients = CU_add_suite("Suite_Clients", initSuiteClients, cleanSuiteClients);
	CU_pSuite pSuiteBuildings = CU_add_suite("Suite_Buildings", initSuiteBuildings, cleanSuiteBuildings);
	//CU_pSuite pSuitePros = CU_add_suite("Suite_Pros", initSuitePros, cleanSuitePros;
	
	CU_add_test(pSuiteClients, "Test clients file parsing", testClientsFileParse);

	CU_add_test(pSuiteBuildings, "Test building file parsing", testBuildingsFileParse);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	
	// Clean test registry
	CU_cleanup_registry();
	
	return CU_get_error();
}
