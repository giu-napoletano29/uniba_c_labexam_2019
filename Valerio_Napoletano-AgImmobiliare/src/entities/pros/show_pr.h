/**
 * @file show_pr.h
 * @author Saverio Valerio
 * @date 23 May 2019
 * @brief Header file containing prototypes related to the "show pros" functions.
 */

#ifndef ENTITIES_PROS_SHOW_PR_H_
#define ENTITIES_PROS_SHOW_PR_H_

void showProData(professional *pr, potential *allPts, unsigned int numRecords);
int showAllPros(professional *allPros, potential *allPts, unsigned int numRecords);

#endif /* ENTITIES_PROS_SHOW_PR_H_ */
