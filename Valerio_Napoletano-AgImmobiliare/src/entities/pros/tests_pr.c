/**
 * @file tests_pr.c
 * @author Saverio Valerio
 * @date 12 June 2019
 * @brief Functions that made up the "professionals" CUnit test suite
 */

#include <stdio.h> 
#include "CUnit/Basic.h" 

#include "../../datatypes.h"
#include "../../file_utils.h"

#include "misc_pr.h"
#include "files_pr.h"
#include "files_pts.h"

// Test filenames
char prosTestFile[MAX_STRING_SIZE] = "pros-test.dat";
char ptsTestFile[MAX_STRING_SIZE] = "pros_potentials-test.dat";

/**
 * @brief Initialize the "professionals" test suite creating a temp file with mock building data.
 * @return 0 success or 1 for error
 */
int initSuitePros() {
	// Initialize to "error".
	// Cunit considers 0 as a success and every other value as an error.
	unsigned short int result = 1;
	FILE *filePtrPro, *filePtrPts;

	// One test professional and its potential
	professional testPro;
	initProsArray(&testPro, 1);

	potential testPts;
	initPotentialsArray(&testPts, 1);

	// Create a test file
	filePtrPro = fopen(prosTestFile, "w+");
	filePtrPts = fopen(ptsTestFile, "w+");

	if (checkFile(filePtrPro) && checkFile(filePtrPts)) {
		rewind(filePtrPro);
		rewind(filePtrPts);

		// Add test data for a professional
		strcpy(testPro.id, "VLRSVR99E17A669R");
		strcpy(testPro.name, "SAVERIO");
		strcpy(testPro.surname, "VALERIO");
		strcpy(testPro.area, "BARLETTA");
		strcpy(testPro.phone, "3273456789");
		strcpy(testPro.email, "s.valerio5@studenti.uniba.it");
		// 12/06/2019 in Unix Epoch Time
		testPro.regDate = 1560330074;
		testPro.buildingsSold = 16;

		// Add potential
		strcpy(testPts.id, "VLRSVR99E17A669R");
		strcpy(testPts.content, "Ha molta dimestichezza nella vendita di case vacanza");

		result = 0;

		// Print data to test file
		appendProToFile(&testPro, prosTestFile);
		appendPtsToFile(&testPts, ptsTestFile);
	}

	fclose(filePtrPro);
	fclose(filePtrPts);

	return result;
}

/**
 * @brief Cleans up the test suite removing the temp clients file
 * @return
 */
int cleanSuitePros() {
	// Delete test files
	remove(prosTestFile);
	remove(ptsTestFile);

	return 0;
}

/**
 * @brief Test method that checks if the file load and parsing works as expected.
 * 
 * Runs loadClientsFile() with the test file created by initSuiteClients().
 * Converting regDate to a string is necessary because CUnit does not seems to work well with
 * "time_t" data type.
 */
void testProsFileParse() {
	struct tm *clDate = { 0 };
	char dateBuffer[11] = "";

	// One test professional and its potential
	professional testPro;
	initProsArray(&testPro, 1);

	potential testPts;
	initPotentialsArray(&testPts, 1);

	// Load and parse the temp buildings file
	CU_ASSERT(loadProsFile(&testPro, prosTestFile));
	CU_ASSERT(loadPotentialsFile(&testPts, ptsTestFile));

	// Check that fields has been loaded correctly in the struct
	CU_ASSERT_STRING_EQUAL(testPro.id, "VLRSVR99E17A669R");
	CU_ASSERT_STRING_EQUAL(testPro.name, "SAVERIO");
	CU_ASSERT_STRING_EQUAL(testPro.surname, "VALERIO");
	CU_ASSERT_STRING_EQUAL(testPro.area, "BARLETTA");
	CU_ASSERT_STRING_EQUAL(testPro.phone, "3273456789");
	CU_ASSERT_STRING_EQUAL(testPro.email, "s.valerio5@studenti.uniba.it");
	CU_ASSERT_EQUAL(testPro.buildingsSold, 16);

	// Convert regDate to string and check assertion on the latter
	clDate = localtime(&testPro.regDate);
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);
	CU_ASSERT_STRING_EQUAL(dateBuffer, "12/06/2019");

	// Check potential
	CU_ASSERT_STRING_EQUAL(testPts.id, "VLRSVR99E17A669R");
	
	// Remove \n from content field in order to make the CU_ASSERT_STRING_EQUAL work properly.
	sscanf(testPts.content, "%[^\n]", testPts.content);

	CU_ASSERT_STRING_EQUAL(testPts.content, "Ha molta dimestichezza nella vendita di case vacanza");

}
