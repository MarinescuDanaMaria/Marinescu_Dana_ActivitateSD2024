#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugareAeroport(struct Aeroport* aeroporturi, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
		copie[i] = aeroporturi[i];

	(*dimensiune)++;

	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* aeroporturi;
	aeroporturi = NULL;

	FILE* f = fopen(numeFisier, "r");

	if (f) {
		char buffer[100];
		(*nrAeroporturi) = 0;
		while (fgets(buffer, 99, f) != NULL) {
		…
[16:15, 05/03/2024] Dana Maria: #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugareAeroport(struct Aeroport* aeroporturi, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
		copie[i] = aeroporturi[i];

	(*dimensiune)++;

	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* aeroporturi;
	aeroporturi = NULL;

	FILE* f = fopen(numeFisier, "r");

	if (f) {
		char buffer[100];
		(*nrAeroporturi) = 0;
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";

			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);

			token = strtok(NULL, delimitator);

			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			aeroporturi = adaugareAeroport(aeroporturi, aeroport, nrAeroporturi);
		}

		fclose(f);

		return aeroporturi;
	}
	else printf("Eroare deschidere fisier!\n");
}

void afisareAeroport(const struct Aeroport aeroport) {
	printf("ID: %d, Nume: %s, Nr. Terminale: %d\n", aeroport.id, aeroport.nume, aeroport.nrTerminale);
}

void afisareVectorAeroporturi(const struct Aeroport* aeroporturi, int dimensiune) {
	printf("Afisare vector:\n");
	for (int i = 0; i < dimensiune; i++) {
		afisareAeroport(aeroporturi[i]);
	}
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
		free(aeroporturi[i]);
	}

	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = NULL;
}

void main() {
	int dimensiune;
	struct Aeroport* aeroporturi = NULL;

	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);

	afisareVectorAeroporturi(aeroporturi, &dimensiune);

	dezalocareVector(aeroporturi, dimensiune);
}