/**
 * @file misc.c
 * @author Saverio Valerio
 * @date 28 May 2019
 * @brief File containing misc functions used by the "professional" entity.
 */

#include <string.h>

#include "../../datatypes.h"

/**
 *  Initialize an array of structs of "potentials".
 *
 * @param po "Potential" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initPotentialsArray(potential *po, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(po[i].id, "");
		strcpy(po[i].content, "");
	}
}

/**
 * Initialize an array of structs of professionals.
 * @param pro "Professional" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initProsArray(professional *pro, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(pro[i].id, "");
		strcpy(pro[i].name, "");
		strcpy(pro[i].surname, "");
		strcpy(pro[i].area, "");
		strcpy(pro[i].phone, "");
		strcpy(pro[i].email, "");
		pro[i].reg_date = 0;
		pro[i].buildings_sold = 0;
	}
}
