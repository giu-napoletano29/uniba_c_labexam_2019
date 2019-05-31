/**
 * @file consts.h
 * @author Saverio Valerio
 * @date 13 May 2019
 * @brief File containing general constants available to the program.
 */

#ifndef CONSTS_H
#define CONSTS_H

/**
 * It is important to specify a field width for the %s string placeholder for avoiding buffer overflows.
 * Scanf does not support any field width restriction specification using a variable.
 *
 * Therefore we are limiting the scanf here using some constants tricks and the STRING_SIZE const value.
 *
 * @see https://stackoverflow.com/questions/25410690/scanf-variable-length-specifier
 */
#define STR2(x) #x
#define STR(X) STR2(X)

/** Max string size */
#define STRING_SIZE 50

/** User budget limits (in euro) */
#define MIN_USER_BUDGET 100

/** One bilion */
#define MAX_USER_BUDGET 1000000000

#define DAY_IN_SECONDS 86400

/** How many days until the programm will prompt the user to delete a client */
#define CLIENT_EXPIRE_DAYS 30

#endif /* CONSTS_H */
