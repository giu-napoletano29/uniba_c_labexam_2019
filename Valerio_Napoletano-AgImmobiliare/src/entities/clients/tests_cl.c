/**
 * @file tests_cl.c
 * @author Saverio Valerio
 * @date 12 June 2019
 * @brief Functions that made up the "clients" CUnit test suite
 */

#include <stdio.h> 
#include "CUnit/Basic.h" 

#include "../../datatypes.h"
#include "../../file_utils.h"

#include "misc_cl.h"
#include "files_cl.h"

// Test file name
char clientTestFile[MAX_STRING_SIZE] = "clients_test.dat";

/**
 * @brief Initialize the "clients" test suite creating a temp file with mock building data.
 * @return 0 success or 1 for error
 */
int initSuiteClients() {
	// Initialize to "error".
	// Cunit considers 0 as a success and every other value as an error.
	unsigned short int result = 1;
	FILE *filePtr;

	// One test client
	client testClient;
	initClientsArray(&testClient, 1);

	// Create a test file
	filePtr = fopen(clientTestFile, "w+");

	if (checkFile(filePtr)) {
		rewind(filePtr);

		// Add test data for a client
		strcpy(testClient.id, "VLRSVR99E17A669R");
		strcpy(testClient.name, "SAVERIO");
		strcpy(testClient.surname, "VALERIO");
		testClient.clType = 3;
		strcpy(testClient.companyName, "SAVAL SRL");
		testClient.budget = 200000;
		// 12/06/2019 in Unix Epoch Time
		testClient.regDate = 1560330074;
		testClient.buildingType = 3;

		result = 0;

		// Print data to test file
		appendClientToFile(&testClient, clientTestFile);
	}
	fclose(filePtr);
	return result;
}

/**
 * @brief Cleans up the test suite removing the temp clients file
 * @return
 */
int cleanSuiteClients() {
	// Delete test file
	remove(clientTestFile);

	return 0;
}

/**
 * @brief Test method that checks if the file load and parsing works as expected.
 * 
 * Runs loadClientsFile() with the test file created by initSuiteClients().
 * Converting regDate to a string is necessary because CUnit does not seems to work well with
 * "time_t" data type.
 */
void testClientsFileParse() {
	struct tm *clDate = { 0 };
	char dateBuffer[11] = "";
	
	client testClient;
	initClientsArray(&testClient, 1);

	// Load and parse the temp buildings file
	CU_ASSERT(loadClientFile(&testClient, clientTestFile));

	// Check that fields has been loaded correctly in the struct
	CU_ASSERT_STRING_EQUAL(testClient.id, "VLRSVR99E17A669R");
	CU_ASSERT_STRING_EQUAL(testClient.name, "SAVERIO");
	CU_ASSERT_STRING_EQUAL(testClient.surname, "VALERIO");
	CU_ASSERT_EQUAL(testClient.clType, 3);
	CU_ASSERT_STRING_EQUAL(testClient.companyName, "SAVAL SRL");
	CU_ASSERT_EQUAL(testClient.budget, 200000);
	
	// Convert regDate to string and check assertion on the latter
	clDate = localtime(&testClient.regDate);
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);
	CU_ASSERT_STRING_EQUAL(dateBuffer, "12/06/2019");

	CU_ASSERT_EQUAL(testClient.buildingType, 3);
}
