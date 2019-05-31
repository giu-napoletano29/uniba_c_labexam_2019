/**
 * @file misc_bl.h
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief File containing misc functions used by the "building" entity.
 */

#include <string.h>

#include "../../datatypes.h"

/**
 * @brief Initialize an array of structs of buildings.
 *
 * @param bl "building" type array of struct.
 * @param size How many elements the array of struct will keep.
 */
void initBuildingsArray(building *bl, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(bl[i].id, "");
		strcpy(bl[i].street, "");
		bl[i].civic = 0;
		strcpy(bl[i].city, "");
		strcpy(bl[i].province, "");
		bl[i].reg_date = 0;
		bl[i].price = 0;
		strcpy(bl[i].owner, "");
		strcpy(bl[i].phone, "");
		bl[i].b_type = flat;
	}
}

