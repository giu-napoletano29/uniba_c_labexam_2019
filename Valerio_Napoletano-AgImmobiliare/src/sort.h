/**
 * @file sort.h
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Header file containing prototypes related to the "sort" functions.
 */
#ifndef SORT_H_
#define SORT_H_

void sortFilePro(professional *pr, int rows);
int sortFileCli(client *cl, int rows);
void sortFileBui(building *bl, int rows);

#endif /* SORT_H_ */
