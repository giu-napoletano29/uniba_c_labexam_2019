/**
 * @file tests.c
 * @author Saverio Valerio
 * @date 12 June 2019
 * @brief Functions that made up the "buildings" CUnit test suite
 */

#include <stdio.h> 
#include "CUnit/Basic.h" 

#include "../../datatypes.h"
#include "../../file_utils.h"

#include "misc_bl.h"
#include "files_bl.h"

// Test file name
char testFile[MAX_STRING_SIZE] = "building_test.dat";

/**
 * @brief Initialize the "buildings" test suite creating a temp file with mock building data.
 * @return 0 success or 1 for error
 */
int initSuiteBuildings() {
	// Initialize to "error".
	// Cunit considers 0 as a success and every other value as an error.
	unsigned short int result = 1;
	FILE *filePtr;

	// One test building
	building testBuilding;
	initBuildingsArray(&testBuilding, 1);

	// Create a test file
	filePtr = fopen(testFile, "w+");

	if (checkFile(filePtr)) {
		rewind(filePtr);

		// Add test data for a building
		testBuilding.id = 93781;
		strcpy(testBuilding.street, "Via Gentileschi");
		testBuilding.civic = 22;
		strcpy(testBuilding.city, "Barletta");
		strcpy(testBuilding.province, "BT");
		// 12/06/2019 in Unix Epoch Time
		testBuilding.regDate = 1560330074;
		testBuilding.price = 150000.60;
		strcpy(testBuilding.owner, "Saverio Valerio");
		strcpy(testBuilding.phone, "3274564477");
		testBuilding.ctrType = 1;
		testBuilding.builType = 1;
		// Still on sale
		testBuilding.soldOn = 0;

		result = 0;

		// Print data to test file
		appendBuildingToFile(&testBuilding, testFile);
	}
	fclose(filePtr);
	return result;
}

/**
 * @brief Cleans up the test suite removing the temp buildings file
 * @return
 */
int cleanSuiteBuildings() {
	// Delete test file
	remove(testFile);

	return 0;
}

/**
 * @brief Test method that checks if the file load and parsing works as expected.
 * 
 * Runs loadBuildingsFile() with the test file created by initSuiteBuildings().
 * Converting regDate to a string is necessary because CUnit does not seems to work well with
 * "time_t" data type.
 */
void test_buildingsFileParse() {
	struct tm *clDate = { 0 };
	char dateBuffer[11] = "";
	
	building testBuilding;
	initBuildingsArray(&testBuilding, 1);

	// Load and parse the temp buildings file
	CU_ASSERT(loadBuildingsFile(&testBuilding, testFile));

	// Check that fields has been loaded correctly in the struct
	CU_ASSERT_EQUAL(testBuilding.id, 93781);
	CU_ASSERT_STRING_EQUAL(testBuilding.street, "VIA GENTILESCHI");
	CU_ASSERT_EQUAL(testBuilding.civic, 22);
	CU_ASSERT_STRING_EQUAL(testBuilding.city, "BARLETTA");
	CU_ASSERT_STRING_EQUAL(testBuilding.province, "BT");

	// Convert regDate to string and check assertion on the latter
	clDate = localtime(&testBuilding.regDate);
	strftime(dateBuffer, 11, "%d/%m/%Y", clDate);
	CU_ASSERT_STRING_EQUAL(dateBuffer, "12/06/2019");

	CU_ASSERT_EQUAL(testBuilding.price, 150000.60);
	CU_ASSERT_STRING_EQUAL(testBuilding.owner, "SAVERIO VALERIO");
	CU_ASSERT_STRING_EQUAL(testBuilding.phone, "3274564477");
	CU_ASSERT_EQUAL(testBuilding.builType, 1);
	CU_ASSERT_EQUAL(testBuilding.ctrType, 1);
	CU_ASSERT_EQUAL(testBuilding.soldOn, 0);
}
