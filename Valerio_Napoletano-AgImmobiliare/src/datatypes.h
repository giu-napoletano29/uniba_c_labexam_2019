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
 * @brief Data type for handling the client type
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
} clientType;

/**
 * @brief Data type for handling the building type
 */
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
} buildingType;

/**
 * @brief Data type for handling the contract type
 */
typedef enum {
	/** Affitto */
	rent,
	/** Vendita */
	sale
} contractType;

typedef struct {
	char id[MAX_STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char name[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	clientType clType; /**< Client type */
	char companyName[MAX_STRING_SIZE]; /**< Company name (if type is company) */
	unsigned int budget; /**< Integer is enough, does not make any sense having a "float/double" budget */
	time_t regDate; /**< Registration date in Epoch time */
	buildingType buildingType; /**< Type of building that needs to be searched */
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
	time_t regDate; /**< Registration date in Epoch time */
	unsigned int buildingsSold; /**< Number of buildings that this professional has sold */
	bool toDelete; /**< If true this professional won't be saved in the file */
} professional;

typedef struct {
	char id[MAX_STRING_SIZE]; /**< "Codice Fiscale" in Italy */
	char content[MAX_TEXT_SIZE];
	bool toDelete; /**< If true this potential won't be saved in the file */
} potential;

typedef struct {
	unsigned int id;
	char street[MAX_STRING_SIZE];
	unsigned short int civic;
	char city[MAX_STRING_SIZE];
	char province[MAX_STRING_SIZE];
	time_t regDate; /**< Registration date in Epoch time */
	double price;
	char owner[MAX_STRING_SIZE];
	// Owner phone number
	char phone[MAX_STRING_SIZE];
	time_t soldOn; /**< Sold date in Epoch time. If it's 0, then the building is still on sale */
	contractType ctrType;
	buildingType builType;
	bool toDelete; /**< If true this building won't be saved in the file */
} building;

#endif
