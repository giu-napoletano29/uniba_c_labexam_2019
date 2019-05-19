/*
 * datatypes.h
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#ifndef DATATYPES_H
#define DATATYPES_H

#include "consts.h"

typedef struct {
	short int day;
	short int month;
	short int year;
} date;

typedef enum {
	family, single, company, government
} client_type;

typedef enum {
	// Appartamento
	flat,
	/*
	 Alloggio su due piani sovrapposti
	 in cui la «zona notte» e la «zona giorno» sono collegate mediante una scala interna.
	 */
	duplex,
	// Villa
	house,
	// Casale
	farmhouse,
	// Attico
	attic
} property_type;

typedef struct {
	// "Codice Fiscale" in Italy
	char id[STRING_SIZE];
	char name[STRING_SIZE];
	char surname[STRING_SIZE];
	// Client type (company, private, etc..)
	client_type cl_type;
	// Company name (if type is company)
	char company_name[STRING_SIZE];
	int budget;
	// Registration date
	date reg_date;
	// Type of the property that needs to be searched
	property_type pr_search_type;
} clients;

typedef struct {
	int id;
	char name[STRING_SIZE];
	// Registration date
	date reg_date;
	int price;
	char locality[STRING_SIZE];
	char type[STRING_SIZE];
} property;

// -- UTILS --
// readInteger result struct
typedef struct {
	bool error;
	int val;
} int_result;

// readString result struct
typedef struct {
	bool error;
	char val[STRING_SIZE];
} str_result;

#endif
