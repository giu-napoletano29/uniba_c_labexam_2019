/*
 * datatypes.h
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#define STRING_SIZE 50

enum client_type {
	family, single, company, government
};

typedef struct {
	char name[STRING_SIZE];
	char surname[STRING_SIZE];
	// Client type (company, private, etc..)
	char cl_type[STRING_SIZE];
	// Company name (if type is company)
	char company_name[STRING_SIZE];
	int budget;
	// Type of the property that needs to be searched
	char pr_search_type[STRING_SIZE];
} clients;

enum property_type {
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
};

typedef struct {
	int id;
	char name[STRING_SIZE];
	// Registration date
	date reg_date;
	int price;
	char locality[STRING_SIZE];
	char type[STRING_SIZE];
} property;
