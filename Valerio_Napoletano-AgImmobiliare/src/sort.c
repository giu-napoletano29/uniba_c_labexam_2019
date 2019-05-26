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

void sortFilePro(professionals *pr, int rows){

}

void sortFileCli(clients *cl, int rows){

}
void sortFileBui(building *bl, int rows){
	building cmp;

	for(int j = 0; j<rows; j++){
		for(int i = 0; i<rows; i++){
			if(strcmp(bl[j].owner, bl[i].owner)<0){
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
	showAllBuildings(bl, rows);
	system("pause");
}
