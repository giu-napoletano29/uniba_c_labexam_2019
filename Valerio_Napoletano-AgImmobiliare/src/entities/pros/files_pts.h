/**
 * @file files_pts.h
 * @author Saverio Valerio
 * @date 6 June 2019
 * @brief Header file with prototypes of functions related to the professionals' "potential".
 */

void findPotential(char id[], potential *pr, unsigned int num_profess);
void parsePotentialsFile(FILE *filePtr, potential *pr);
int loadPotentialsFile(potential *allPts, char *filename);
int appendPtsToFile(potential *pt, char *filename);
void rewritePtsToFile(potential *allPts, unsigned int rows, char *filename);
