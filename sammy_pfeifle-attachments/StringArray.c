#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#define ANZAHL_WOERTER 3500
//#define ANZAHL_WOERTER  20000
//#define ANZAHL_WOERTER  28284
//#define ANZAHL_WOERTER  34641
//#define ANZAHL_WOERTER  40000
//#define ANZAHL_WOERTER  44721
//#define ANZAHL_WOERTER  48990
//#define ANZAHL_WOERTER  52915
//#define ANZAHL_WOERTER  56569
//#define ANZAHL_WOERTER  60000
//#define ANZAHL_WOERTER  63246

//int woerterEinlesen(char** woerter)
//{
//	char wort[100];
//	int anzahl = 0;
//
//	printf("Worte eingeben (Beenden mit '<')\n");
//	while (anzahl < ANZAHL_WOERTER) {
//		printf("> ");
//		scanf("%s", wort);
//		if ('<' == wort[0]) {
//			break;
//		}
//		woerter[anzahl] = (char*)malloc(strlen(wort) + 1); // String-Abschlusszeichen berücksichtigen
//		if (woerter[anzahl] != NULL) {
//			strcpy(woerter[anzahl], wort);
//			anzahl++;
//		}
//		else {
//			printf("FEHLER: nicht genug Speicher vorhanden\n");
//			break;
//		}
//	}
//	printf("%d Worte gelesen.\n", anzahl);
//	/* Alle ungenutzten Zeiger in dem Array woerter auf NULL setzen */
//	for (int i = anzahl; i < ANZAHL_WOERTER; i++) {
//		woerter[i] = NULL;
//	}
//
//	return anzahl;
//}

int woerterEinlesen(char** woerter)
{
	char wort[100];
	int i, anzahl = 0, gelesen;
	FILE* datei;

	datei = fopen("woerter.txt", "r");
	if (datei != NULL) {
		while (anzahl < ANZAHL_WOERTER) {
			gelesen = fscanf(datei, "%s", wort);
			if (EOF == gelesen) {
				break;
			}
			woerter[anzahl] = (char*)malloc(strlen(wort) + 1); // String-Abschlusszeichen berücksichtigen
			if (woerter[anzahl] != NULL) {
				strcpy(woerter[anzahl], wort);
				anzahl++;
			}
			else {
				printf("FEHLER: nicht genug Speicher vorhanden\n");
				break;
			}
		}
		fclose(datei);
		printf("%d Worte gelesen.\n", anzahl);
	}
	else {
		printf("FEHLER: Datei nicht vorhanden\n");
	}
	/* Alle ungenutzten Zeiger in dem Array woerter auf NULL setzen */
	for (i = anzahl; i < ANZAHL_WOERTER; i++) {
		woerter[i] = NULL;
	}

	return anzahl;
}

woerterAusgeben(char** woerter, int anzahl)
{
	printf("Die ersten 10 Worte:\n");
	if (anzahl > 10) {
		anzahl = 10;
	}
	for (int i = 0; i < anzahl; i++) {
		printf("%s ", woerter[i]);
	}
	printf("\n");
}

//char* lineareSuche(char** woerter, int anzahl, char *gesuchtesWort)
//{
//	for (int i = 0; i < anzahl; i++) {
//		if (strcmp(woerter[i], gesuchtesWort) == 0) {
//			return woerter[i];
//		}
//	}
//	return NULL;
//}

char* lineareSuche(char** woerter, int anzahl, char* gesuchtesWort)
{
	static int i = 0;
	for (; i < anzahl; i++) {
		if (strcmp(woerter[i], gesuchtesWort) == 0) {
			i++;
			return woerter[i];
		}
	}
	i = 0;
	return NULL;
}

woerterUmdrehen(char** woerter, int anzahl)
{
	char* temp;
	for (int i = 0; i < anzahl / 2; i++) {
		temp = woerter[i];
		woerter[i] = woerter[anzahl - 1 - i];
		woerter[anzahl - 1 - i] = temp;
	}
}

woerterLoeschen(char** woerter, int anzahl)
{
	for (int i = 0; i < anzahl; i++) {
		free(woerter[i]);
		woerter[i] = NULL;
	}
}

bubblesort(char** woerter, int anzahl)
{
	char* temp;
	int i, j = 0, sortiert = 0;
	while (sortiert == 0) {
		j++;
		sortiert = 1;
		anzahl--;
		for (i = 0; i < anzahl; i++)
			if (strcmp(woerter[i], woerter[i + 1]) > 0) {
				temp = woerter[i];
				woerter[i] = woerter[i + 1];
				woerter[i + 1] = temp;
				sortiert = 0;
			}
	}
	printf("Anzahl: %d\n\n", j);
}

gnomesort(char** woerter, int anzahl)
{
	char* temp;
	int i = 1;
	do {
		if (strcmp(woerter[i - 1], woerter[i]) > 0) {
			temp = woerter[i];
			woerter[i] = woerter[i - 1];
			woerter[i - 1] = temp;
			if (i == 1) {
				i++;
			}
			else {
				i--;
			}
		}
		else {
			i++;
		}
	} while (i < anzahl);
}

insertionsort(char** woerter, int anzahl)
{
	char* temp;
	int i, j;
	for (i = anzahl - 2; i >= 0; i--) {
		temp = woerter[i];
		for (j = i + 1; j < anzahl; j++) {
			if (strcmp(temp, woerter[j]) > 0) {
				woerter[j - 1] = woerter[j];
			}
			else {
				break;
			}
		}
		woerter[j - 1] = temp;
	}
}

selectionsort(char** woerter, int anzahl)
{
	char* temp;
	int i, j, jmax;
	for (i = anzahl - 1; i > 0; i--) {
		jmax = i; // bei sortierten Wörtern ist das das Maximum
		temp = woerter[jmax];
		for (j = 0; j < i; j++) {
			if (strcmp(temp, woerter[j]) < 0) { 
				jmax = j;
				temp = woerter[jmax];
			}
		}
		woerter[jmax] = woerter[i];
		woerter[i] = temp;
	}
}

quicksort(char** woerter, int anzahl)
{
	int i, j, pivotIndex = anzahl / 2;
	//if (pivotIndex >= anzahl) {
	//	pivotIndex = 0;
	//}
	char* temp, * pivotElement = woerter[pivotIndex];

	// Rekursionsabbruch
	if (anzahl < 2) {
		return;
	}

	i = 0;
	j = anzahl - 1;
	while (1) {
		// Suche von links
		while (i < anzahl && strcmp(woerter[i], pivotElement) <= 0) {
			i++;
		}
		// Suche von rechts
		while (j >= 0 && strcmp(woerter[j], pivotElement) >= 0) {
			j--;
		}
		// tauschen
		if (i < j) {
			temp = woerter[i];
			woerter[i] = woerter[j];
			woerter[j] = temp;
		}
		else {
			// es gilt j < i   (j == i kann nicht vorkommen)
			// wenn nötig das pivotElement zwischen die Teilbereiche legen
			if (pivotIndex < j) {
				temp = woerter[pivotIndex];
				woerter[pivotIndex] = woerter[j];
				woerter[j] = temp;
				j--;
			}
			else if (i < pivotIndex) {
				temp = woerter[pivotIndex];
				woerter[pivotIndex] = woerter[i];
				woerter[i] = temp;
				i++;
			}
			break;
		}
	}
	// Rekursives Sortieren der Teilbereiche
	quicksort(woerter, j + 1);
	quicksort(woerter + i, anzahl - i);
}

char* binaereSuche(char** woerter, int anzahl, char* gesuchtesWort) {
	int cmp, mittlererIndex = anzahl / 2;
	char* mittleresElement = woerter[mittlererIndex];
	if (anzahl < 1)
		return NULL;
	cmp = strcmp(gesuchtesWort, mittleresElement);
	if (cmp == 0)
		return mittleresElement;
	if (cmp < 0)
		return binaereSuche(woerter, mittlererIndex, gesuchtesWort);
	else
		return binaereSuche(woerter + mittlererIndex + 1, anzahl - mittlererIndex - 1, gesuchtesWort);
}

int check(char** woerter, int anzahl) {
	for (int i = 1; i < anzahl; i++) {
		if (strcmp(woerter[i - 1], woerter[i]) > 0) {
			return 1;
		}
	}
	return 0;
}

// liefert den worst case für quicksort mit mittlerem Pivot-Element
// Voraussetzung: woerter müssen sortiert sein
worst_case(char** woerter, int anzahl) {
	int i, j;
	char* temp;

	if (check(woerter, anzahl)) {
		printf("Fehler: Woerter muessen sortiert sein\n");
		return;
	}
	for (i = anzahl - 2; i >= 0; i--) {
		j = (anzahl - i) / 2 + i;
		temp = woerter[i];
		woerter[i] = woerter[j];
		woerter[j] = temp;
	}
}

main()
{
	char* woerter[ANZAHL_WOERTER];
	char gesuchtesWort[100];
	char* ptr = NULL;
	int anzahl, sel;
	int tick_count;

	/* Woerter einlesen */
	anzahl = woerterEinlesen(woerter);
	if (0 == anzahl) {
		return;
	}

	while (1)
	{
		printf("1 - ausgeben\n2 - suchen\n3 - umdrehen\n");
		printf("4 - bubblesort\n5 - gnomesort\n6 - insertionsort\n7 - selectionsort\n8 - bin. suchen\n");
		printf("9 - quicksort\n10 - Sortierung pruefen\n11 - worst case erzeugen\n > ");
		scanf("%d", &sel);
		tick_count = GetTickCount();
		switch (sel)
		{
		case 1:
			/* Woerter ausgeben */
			woerterAusgeben(woerter, anzahl);
			break;
		case 2:
			/* ein Wort suchen */
			printf("gesuchtesWort eingeben: ");
			scanf("%s", gesuchtesWort);
			ptr = lineareSuche(woerter, anzahl, gesuchtesWort);
			if (ptr == NULL) {
				printf("Gesuchtes Wort nicht gefunden\n");
			}
			else {
				printf("Gesuchtes Wort hat die Adresse %p\n", ptr);
			}
			break;
		case 3:
			/* Reihenfolge umdrehen */
			woerterUmdrehen(woerter, anzahl);
			printf("Reihenfolge geaendert\n");
			break;
		case 4:
			/* bubblesort */
			bubblesort(woerter, anzahl);
			printf("Woerter alphabetisch sortiert\n");
			break;
		case 5:
			/* gnomesort */
			gnomesort(woerter, anzahl);
			printf("Woerter alphabetisch sortiert\n");
			break;
		case 6:
			/* insertionsort */
			insertionsort(woerter, anzahl);
			printf("Woerter alphabetisch sortiert\n");
			break;
		case 7:
			/* selectionsort */
			selectionsort(woerter, anzahl);
			printf("Woerter alphabetisch sortiert\n");
			break;
		case 8:
			/* ein Wort in sortierten Daten suchen */
			printf("gesuchtesWort eingeben: ");
			scanf("%s", gesuchtesWort);
			ptr = binaereSuche(woerter, anzahl, gesuchtesWort);
			if (ptr == NULL) {
				printf("Gesuchtes Wort nicht gefunden\n");
			}
			else {
				printf("Gesuchtes Wort hat die Adresse %p\n", ptr);
			}
			break;
		case 9:
			/* quicksort */
			quicksort(woerter, anzahl);
			printf("Woerter alphabetisch sortiert\n");
			break;
		case 10:
			/* Sortierung prüfen */
			if (check(woerter, anzahl)) {
				printf("Sortierfehler\n");
			}
			else {
				printf("Sortierung OK\n");
			}
			break;
		case 11:
			/* worst case erzeugen */
			worst_case(woerter, anzahl);
			printf("Woerter gemischt\n");
			break;
		default:
			/* Woerter loeschen */
			woerterLoeschen(woerter, anzahl);
			anzahl = 0;
			return;
		}
		printf("Ticks: %d\n", GetTickCount() - tick_count);
	}
}
