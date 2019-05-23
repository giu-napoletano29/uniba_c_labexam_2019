/**
 * @file datatypes.h
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief File containing all the used datatypes.
 */

#ifndef DATATYPES_H
#define DATATYPES_H

#include "consts.h"

/**
 * @brief Struct for handling a date (made up by day, month and year)
 */
typedef struct {
	short int day;
	short int month;
	short int year;
} date;

/**
 * @brief Struct for handling the client type
 */
typedef enum {
	/** Famiglia */
	family,
	/** Persona fisica celibe/nubile */
	single,
	/** Azienda */
	company,
	/** Stato */
	government
} client_type;

typedef enum {
	/** Appartamento */
	flat,
	/** Alloggio su due piani sovrapposti dove la "zona notte" e la "zona giorno" sono collegate mediante una scala interna. */
	duplex,
	/** Villa */
	house,
	/** Casale */
	farmhouse,
	/** Attico */
	attic
} building_type;

typedef struct {
	char id[STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[STRING_SIZE];
	char surname[STRING_SIZE];
	client_type cl_type; /**< Client type (company, private, etc..) */
	char company_name[STRING_SIZE]; /**< Company name (if type is company) */
	int budget;
	date reg_date; /**< Registration date */
	building_type building_type; /**< Type of building that needs to be searched */
} clients;

typedef struct {
	char id[STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[STRING_SIZE];
	char surname[STRING_SIZE];
	char area[STRING_SIZE]; /**< Area of "competence" */
	// Phone number
	char phone[STRING_SIZE];
	// Email address
	char email[STRING_SIZE];
	date reg_date;
	int buildings_sold; /**< Number of buildings that this professional has sold */
} professionals;

typedef struct {
	char id[STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char content[STRING_SIZE];
} potential;

typedef struct {
	char id[STRING_SIZE];
	char street[STRING_SIZE];
	short int civic;
	char city[STRING_SIZE];
	char province[STRING_SIZE];
	// Registration date
	date reg_date;
	int price;
	char owner[STRING_SIZE];
	// Owner phone number
	char phone[STRING_SIZE];
	building_type b_type;
} building;

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
