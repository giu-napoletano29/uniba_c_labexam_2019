/**
 * @file files_pts.h
 * @author Saverio Valerio
 * @date 6 June 2019
 * @brief Header file with prototypes of functions related to the professionals' "potential".
 */

void findPotential(char id[], potential *pr, int num_profess);
void parsePotentialsFile(FILE *filePtr, potential *pr);
void loadPotentialsFile(potential *allPts);
int appendPtsToFile(potential *pt);
void rewritePtsToFile(potential *allPts, int rows);
