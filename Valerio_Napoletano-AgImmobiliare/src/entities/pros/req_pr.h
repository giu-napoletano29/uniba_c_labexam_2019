/**
 * @file req_cl.c
 * @author Saverio Valerio
 * @date 1 June 2019
 * @brief Header file containing prototypes related to the "request professionals' data" functions.
 */

#ifndef ENTITIES_PROS_REQ_PR_H_
#define ENTITIES_PROS_REQ_PR_H_

void reqProCF(professional *pr);
void reqProName(professional *pr);
void reqProSurname(professional *pr);
void reqProArea(professional *pr);
void reqProPhone(professional *pr);
void reqProEmail(professional *pr);
void reqProSoldBuildings(professional *pr);
void reqProPotential(professional *pr, potential *pt);

#endif /* ENTITIES_PROS_REQ_PR_H_ */
