/**
 * @file consts.h
 * @author Saverio Valerio
 * @date 13 May 2019
 * @brief File containing general macros available to the program.
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

/**
*  Macro for defining if the test function can be called directly from the main menu
 * This is useful when we want to distribute our software in production, therefore we need to easily hide tests to the "nomal" users
 */
#define SHOW_TESTS_MAIN_MENU true

/** If needed, tests can be executed at the startup, without waiting for the menu choice */
#define RUN_TESTS_AT_STARTUP false

/** 
 * Sadly, ANSI escape sequences for setting colors are supported only on Windows 10, build 16257 onwards, (or GNU/Linux - macOS)
 * basically the Windows 10 Anniversary Update released in 2016.
 * 
 * Also, checking the Windows version number is a real pain, basically thanks to the deprecation of GetVersion() and GetVersionEx()
 * by Microsoft that makes these functions unreliable on Windows 10.
 * 
 * Using the newly "Version Helper functions" also requires the usage of the Visual C++ toolset, pretty overkill for our usage.
 * 
 * This is why using this macro is required. 
 * It's false as default because target computers in our university should run Windows 7. 
 * 
 * @see https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 * @see https://github.com/ytdl-org/youtube-dl/issues/15758
 * @see https://docs.microsoft.com/en-us/windows/desktop/SysInfo/targeting-your-application-at-windows-8-1
 */
#define ENABLE_COLORS true

#endif /* CONSTS_H */
