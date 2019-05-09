/*
 * menus.c
 *
 *  Created on: 9 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>

#include "menus.h"
#include "utils.h"

void mainMenu() {
	int choice;

	do {
		newLine();
		puts("-- Agenzia Immobiliare --");
		puts("- MENU PRINCIPALE -");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Clienti");
		puts("2. Professionisti");
		puts("3. Immobili");

		newLine();

		printf("Operazione: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				clientsMenu();
				break;
			case 2:
				professMenu();
				break;
			case 3:
				propertyMenu();
				break;
			default:
				choice = 0;
				break;
		}

	} while (choice <= 0 || choice > 3);
}

void clientsMenu() {
	int choice;

	do {
		newLine();
		puts("--- CLIENTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un cliente");
		puts("2. Modifica un cliente");
		puts("3. Cerca un cliente");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > 4);
}

void professMenu() {
	int choice;

	do {
		newLine();
		puts("--- PROFESSIONISTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un professionista");
		puts("2. Modifica un professionista");
		puts("3. Cerca un professionista");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > 4);
}

void propertyMenu() {
	int choice;

	do {
		newLine();
		puts("--- IMMOBILI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Aggiungi un immobile");
		puts("2. Modifica un immobile");
		puts("3. Cerca un immobile");
		puts("4. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > 4);
}
