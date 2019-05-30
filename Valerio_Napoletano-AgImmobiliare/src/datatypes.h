/**
 * @file datatypes.h
 * @author Saverio Valerio
 * @date 9 May 2019
 * @brief Header file containing all datatypes in use.
 */

#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdbool.h>

#include "consts.h"
#include "time.h"

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
	client_type cl_type; /**< Client type */
	char company_name[STRING_SIZE]; /**< Company name (if type is company) */
	int budget;
	time_t reg_date; /**< Registration date in Epoch time */
	building_type building_type; /**< Type of building that needs to be searched */
	bool toDelete; /**< If true this client won't be saved in the file */
} client;

typedef struct {
	char id[STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[STRING_SIZE];
	char surname[STRING_SIZE];
	char area[STRING_SIZE]; /**< Area of "competence" */
	// Phone number
	char phone[STRING_SIZE];
	// Email address
	char email[STRING_SIZE];
	time_t reg_date; /**< Registration date in Epoch time */
	int buildings_sold; /**< Number of buildings that this professional has sold */
} professional;

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
	time_t reg_date; /**< Registration date in Epoch time */
	int price;
	char owner[STRING_SIZE];
	// Owner phone number
	char phone[STRING_SIZE];
	building_type b_type;
} building;

#endif
