/**
 * @file sort.c
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Sorting functions (with Bubble Sort) in alphabetical order by surname.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "datatypes.h"
#include "file_utils.h"
#include "utils.h"

/**
 * @brief Sort in alphabetical order the professional array of structs by surname.
 *
 * @param pr Array of structs, professional data type
 * @param rows Numbers of records in the "pr" array of structs.
 */
void sortFilePro(professional *pr, int rows) {
	professional cmp;
	int index_min = 0;

	for (int j = 0; j < rows - 1; j++) {
		index_min = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp(pr[i].surname, pr[index_min].surname) < 0) {
				index_min = i;
			}
		}	// Element are moved at the end of the comparison process to avoid useless operation
		cmp.buildings_sold = pr[j].buildings_sold;
		pr[j].buildings_sold = pr[index_min].buildings_sold;
		pr[index_min].buildings_sold = cmp.buildings_sold;

		cmp.reg_date = pr[j].reg_date;
		pr[j].reg_date = pr[index_min].reg_date;
		pr[index_min].reg_date = cmp.reg_date;

		strcpy(cmp.name, pr[j].name);
		strcpy(pr[j].name, pr[index_min].name);
		strcpy(pr[index_min].name, cmp.name);

		strcpy(cmp.id, pr[j].id);
		strcpy(pr[j].id, pr[index_min].id);
		strcpy(pr[index_min].id, cmp.id);

		strcpy(cmp.surname, pr[j].surname);
		strcpy(pr[j].surname, pr[index_min].surname);
		strcpy(pr[index_min].surname, cmp.surname);

		strcpy(cmp.area, pr[j].area);
		strcpy(pr[j].area, pr[index_min].area);
		strcpy(pr[index_min].area, cmp.area);

		strcpy(cmp.phone, pr[j].phone);
		strcpy(pr[j].phone, pr[index_min].phone);
		strcpy(pr[index_min].phone, cmp.phone);

		strcpy(cmp.email, pr[j].email);
		strcpy(pr[j].email, pr[index_min].email);
		strcpy(pr[index_min].email, cmp.email);
	}
}

/**
 * @brief Sort in alphabetical order the client array of structs by surname.
 *
 * @param cl Array of structs, client data type
 * @param rows Numbers of records in the "cl" array of structs.
 */
void sortFileCli(client *cl, int rows) {
	client cmp;
	int index_min = 0;

	for (int j = 0; j < rows - 1; j++) {
		index_min = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp(cl[i].surname, cl[index_min].surname) < 0) {
				index_min = i;
			}
		}	// Element are moved at the end of the comparison process to avoid useless operation
		cmp.budget = cl[j].budget;
		cl[j].budget = cl[index_min].budget;
		cl[index_min].budget = cmp.budget;

		cmp.cl_type = cl[j].cl_type;
		cl[j].cl_type = cl[index_min].cl_type;
		cl[index_min].cl_type = cmp.cl_type;

		cmp.toDelete = cl[j].toDelete;
		cl[j].toDelete = cl[index_min].toDelete;
		cl[index_min].toDelete = cmp.toDelete;

		cmp.building_type = cl[j].building_type;
		cl[j].building_type = cl[index_min].building_type;
		cl[index_min].building_type = cmp.building_type;

		cmp.reg_date = cl[j].reg_date;
		cl[j].reg_date = cl[index_min].reg_date;
		cl[index_min].reg_date = cmp.reg_date;

		strcpy(cmp.name, cl[j].name);
		strcpy(cl[j].name, cl[index_min].name);
		strcpy(cl[index_min].name, cmp.name);

		strcpy(cmp.id, cl[j].id);
		strcpy(cl[j].id, cl[index_min].id);
		strcpy(cl[index_min].id, cmp.id);

		strcpy(cmp.surname, cl[j].surname);
		strcpy(cl[j].surname, cl[index_min].surname);
		strcpy(cl[index_min].surname, cmp.surname);

		strcpy(cmp.company_name, cl[j].company_name);
		strcpy(cl[j].company_name, cl[index_min].company_name);
		strcpy(cl[index_min].company_name, cmp.company_name);
	}
}

/**
 * @brief Sort in alphabetical order the professional array of structs by owner name.
 *
 * @param bl Array of structs, building data type
 * @param rows Numbers of records in the "bl" array of structs.
 */
void sortFileBui(building *bl, int rows) {
	building cmp;
	int index_min = 0;

	for (int j = 0; j < rows - 1; j++) {
		index_min = j;
		for (int i = j + 1; i < rows; i++) {
			if (strcmp(bl[i].owner, bl[index_min].owner) < 0) {
				index_min = i;
			}
		}
		cmp.civic = bl[j].civic;
		bl[j].civic = bl[index_min].civic;
		bl[index_min].civic = cmp.civic;

		cmp.b_type = bl[j].b_type;
		bl[j].b_type = bl[index_min].b_type;
		bl[index_min].b_type = cmp.b_type;

		cmp.price = bl[j].price;
		bl[j].price = bl[index_min].price;
		bl[index_min].price = cmp.price;

		cmp.reg_date = bl[j].reg_date;
		bl[j].reg_date = bl[index_min].reg_date;
		bl[index_min].reg_date = cmp.reg_date;

		strcpy(cmp.city, bl[j].city);
		strcpy(bl[j].city, bl[index_min].city);
		strcpy(bl[index_min].city, cmp.city);

		cmp.id = bl[j].id;
		bl[j].id = bl[index_min].id;
		bl[index_min].id = cmp.id;

		strcpy(cmp.owner, bl[j].owner);
		strcpy(bl[j].owner, bl[index_min].owner);
		strcpy(bl[index_min].owner, cmp.owner);

		strcpy(cmp.phone, bl[j].phone);
		strcpy(bl[j].phone, bl[index_min].phone);
		strcpy(bl[index_min].phone, cmp.phone);

		strcpy(cmp.province, bl[j].province);
		strcpy(bl[j].province, bl[index_min].province);
		strcpy(bl[index_min].province, cmp.province);

		strcpy(cmp.street, bl[j].street);
		strcpy(bl[j].street, bl[index_min].street);
		strcpy(bl[index_min].street, cmp.street);

		cmp.sold = bl[j].sold;
		bl[j].sold = bl[index_min].sold;
		bl[index_min].sold = cmp.sold;
	}
}
