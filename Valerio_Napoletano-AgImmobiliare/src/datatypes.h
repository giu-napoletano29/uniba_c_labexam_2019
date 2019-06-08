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
	char id[MAX_STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	client_type cl_type; /**< Client type */
	char company_name[MAX_STRING_SIZE]; /**< Company name (if type is company) */
	int budget; /**< Integer is enough, does not make any sense having a "float/double" budget */
	time_t reg_date; /**< Registration date in Epoch time */
	building_type building_type; /**< Type of building that needs to be searched */
	bool toDelete; /**< If true this client won't be saved in the file */
} client;

typedef struct {
	char id[MAX_STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char area[MAX_STRING_SIZE]; /**< Area of "competence" */
	// Phone number
	char phone[MAX_STRING_SIZE];
	// Email address
	char email[MAX_STRING_SIZE];
	time_t reg_date; /**< Registration date in Epoch time */
	int buildings_sold; /**< Number of buildings that this professional has sold */
	bool toDelete; /**< If true this professional won't be saved in the file */
} professional;

typedef struct {
	char id[MAX_STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char content[MAX_TEXT_SIZE];
	bool toDelete; /**< If true this potential won't be saved in the file */
} potential;

typedef struct {
	int id;
	char street[MAX_STRING_SIZE];
	short int civic;
	char city[MAX_STRING_SIZE];
	char province[MAX_STRING_SIZE];
	time_t reg_date; /**< Registration date in Epoch time */
	double price;
	char owner[MAX_STRING_SIZE];
	// Owner phone number
	char phone[MAX_STRING_SIZE];
	building_type b_type;
	bool toDelete; /**< If true this building won't be saved in the file */
} building;

#endif
