/**
 * @file misc_pr.h
 * @author Saverio Valerio
 * @date 28 May 2019
 * @brief Header file with prototypes of misc functions used by the "professional" entity.
 */

#ifndef ENTITIES_PROS_MISC_PR_H_
#define ENTITIES_PROS_MISC_PR_H_

void initPotentialsArray(potential *po, unsigned int size);
void initProsArray(professional *pro, unsigned int size);

int addPro(professional *allPros, potential *allPts, unsigned int numRecords);
int requestProDeletion(professional *allPros, potential *allPts, unsigned int numRecords);
int deletePro(professional *allPros, potential *allPts, unsigned int numRecords, char *toDeleteID, char *prosFile,
		char *ptsFile);
void checkDuplicateProID(potential *po, professional *allPros, unsigned int numRecords);

#endif /* ENTITIES_PROS_MISC_PR_H_ */
