/*
 * sort.c
 *
 *  Created on: 25 mag 2019
 *      Author: Giuseppe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "datatypes.h"
#include "file_utils.h"
#include "utils.h"

void sortFilePro(professionals *pr, int rows) {
	professionals cmp;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < rows; i++) {
			if (strcmp(pr[j].surname, pr[i].surname) < 0) {
				cmp.buildings_sold = pr[i].buildings_sold;
				pr[i].buildings_sold = pr[j].buildings_sold;
				pr[j].buildings_sold = cmp.buildings_sold;

				cmp.reg_date = pr[i].reg_date;
				pr[i].reg_date = pr[j].reg_date;
				pr[j].reg_date = cmp.reg_date;

				strcpy(cmp.name, pr[i].name);
				strcpy(pr[i].name, pr[j].name);
				strcpy(pr[j].name, cmp.name);

				strcpy(cmp.id, pr[i].id);
				strcpy(pr[i].id, pr[j].id);
				strcpy(pr[j].id, cmp.id);

				strcpy(cmp.surname, pr[i].surname);
				strcpy(pr[i].surname, pr[j].surname);
				strcpy(pr[j].surname, cmp.surname);

				strcpy(cmp.area, pr[i].area);
				strcpy(pr[i].area, pr[j].area);
				strcpy(pr[j].area, cmp.area);

				strcpy(cmp.phone, pr[i].phone);
				strcpy(pr[i].phone, pr[j].phone);
				strcpy(pr[j].phone, cmp.phone);

				strcpy(cmp.email, pr[i].email);
				strcpy(pr[i].email, pr[j].email);
				strcpy(pr[j].email, cmp.email);

			}
		}
	}
	/*showAllPros(pr, rows);
	 system("pause");*/
}

void sortFileCli(clients *cl, int rows) {
	clients cmp;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < rows; i++) {
			if (strcmp(cl[j].surname, cl[i].surname) < 0) {
				cmp.budget = cl[i].budget;
				cl[i].budget = cl[j].budget;
				cl[j].budget = cmp.budget;

				cmp.cl_type = cl[i].cl_type;
				cl[i].cl_type = cl[j].cl_type;
				cl[j].cl_type = cmp.cl_type;

				cmp.toDelete = cl[i].toDelete;
				cl[i].toDelete = cl[j].toDelete;
				cl[j].toDelete = cmp.toDelete;

				cmp.building_type = cl[i].building_type;
				cl[i].building_type = cl[j].building_type;
				cl[j].building_type = cmp.building_type;

				cmp.reg_date = cl[i].reg_date;
				cl[i].reg_date = cl[j].reg_date;
				cl[j].reg_date = cmp.reg_date;

				strcpy(cmp.name, cl[i].name);
				strcpy(cl[i].name, cl[j].name);
				strcpy(cl[j].name, cmp.name);

				strcpy(cmp.id, cl[i].id);
				strcpy(cl[i].id, cl[j].id);
				strcpy(cl[j].id, cmp.id);

				strcpy(cmp.surname, cl[i].surname);
				strcpy(cl[i].surname, cl[j].surname);
				strcpy(cl[j].surname, cmp.surname);

				strcpy(cmp.company_name, cl[i].company_name);
				strcpy(cl[i].company_name, cl[j].company_name);
				strcpy(cl[j].company_name, cmp.company_name);

			}
		}
	}
	/*showAllClients(cl, rows);
	 system("pause");*/
}
void sortFileBui(building *bl, int rows) {
	building cmp;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < rows; i++) {
			if (strcmp(bl[j].owner, bl[i].owner) < 0) {
				cmp.civic = bl[i].civic;
				bl[i].civic = bl[j].civic;
				bl[j].civic = cmp.civic;

				cmp.b_type = bl[i].b_type;
				bl[i].b_type = bl[j].b_type;
				bl[j].b_type = cmp.b_type;

				cmp.price = bl[i].price;
				bl[i].price = bl[j].price;
				bl[j].price = cmp.price;

				cmp.reg_date = bl[i].reg_date;
				bl[i].reg_date = bl[j].reg_date;
				bl[j].reg_date = cmp.reg_date;

				strcpy(cmp.city, bl[i].city);
				strcpy(bl[i].city, bl[j].city);
				strcpy(bl[j].city, cmp.city);

				strcpy(cmp.id, bl[i].id);
				strcpy(bl[i].id, bl[j].id);
				strcpy(bl[j].id, cmp.id);

				strcpy(cmp.owner, bl[i].owner);
				strcpy(bl[i].owner, bl[j].owner);
				strcpy(bl[j].owner, cmp.owner);

				strcpy(cmp.phone, bl[i].phone);
				strcpy(bl[i].phone, bl[j].phone);
				strcpy(bl[j].phone, cmp.phone);

				strcpy(cmp.province, bl[i].province);
				strcpy(bl[i].province, bl[j].province);
				strcpy(bl[j].province, cmp.province);

				strcpy(cmp.street, bl[i].street);
				strcpy(bl[i].street, bl[j].street);
				strcpy(bl[j].street, cmp.street);
			}
		}
	}
	/*showAllBuildings(bl, rows);
	 system("pause");*/
}
