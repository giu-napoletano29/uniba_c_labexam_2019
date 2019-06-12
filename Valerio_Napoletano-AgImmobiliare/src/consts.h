/**
 * @file consts.h
 * @author Saverio Valerio
 * @date 13 May 2019
 * @brief File containing general constants available to the program.
 */

#ifndef CONSTS_H
#define CONSTS_H

/** Max string size */
#define MAX_STRING_SIZE 50

/**
 * Max "text" size
 * Useful for the "potential" content
 */
#define MAX_TEXT_SIZE 200

/** User budget limits (in euro) */
#define MIN_USER_BUDGET 100

/** One bilion */
#define MAX_USER_BUDGET 1000000000

#define DAY_IN_SECONDS 86400

/** How many days until the programm will prompt the user to delete a client */
#define CLIENT_EXPIRE_DAYS 30

/** File names */
#define CLIENTS_FNAME "clients.dat"
#define BUILDINGS_FNAME "buildings.dat"
#define PROS_FNAME "professionals.dat"
#define PTS_FNAME "pros_potential.dat"

#endif /* CONSTS_H */
