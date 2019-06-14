/**
 * @file sort.h
 * @author Giuseppe Napoletano
 * @date 25 May 2019
 * @brief Header file containing prototypes related to the "sort" functions.
 */
#ifndef SORT_H_
#define SORT_H_

void sortPros(professional *pr, unsigned int rows);
void sortClients(client *cl, unsigned int rows);
void sortBuildings(building *bl, unsigned int rows);

#endif /* SORT_H_ */
