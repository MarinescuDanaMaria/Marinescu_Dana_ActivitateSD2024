#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// SEMINAR 10 - ARBORI BINARI DE CAUTARE 


// arbore = graf conex aciclic
// arbore binar = graf conex aciclic in care fiecare parinte are maxim 2 descendenti

// Conditii
// 1.cel din stanga sa fie mai mic decat cel din dreapta
// 2.radacina e mai mare

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev 
{
	int id;
	int nrMedii;
	float* medii;
};

struct Nod 
{
	Elev info;
	Nod* st;
	Nod* dr;
};

// INSERARE ARBORE BINAR - se face mereu printr-un nod frunza
void inserareArbore(Nod** radacina, Elev e) 
{
	// verificam daca exista arborele
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > e.id)
		{
			inserareArbore(&((*radacina)->st), e);
		}
		else 
		{
			inserareArbore(&((*radacina)->dr), e);
		}
	}
	else 
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}
Elev citireElev(FILE* fp) 
{
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);
	// alocam spatiu ca e pointer
	// buffer foloseam la char* pt ca nu stiam cata memorie alocam, dar aici stim
	e.medii = malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%f", &(e.medii[i]));
	}
	return e;
}

// FUNCTIA CARE CITESTE ELEVII DINTR-UN FISIER
Nod* citireFisier(char* numeFisier) 
{
	Nod* arbore = NULL;
	// returneaza arborele
	// in fisier o sa fie pe fiecare linie cate un elev, pe prima linie o sa mi se zica cati elevi sunt
	if (!numeFisier) 
	{
		return NULL;
	}
	else {
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(fp);
			// arborele e de tip pointer la nod iar functia asteapta sa primeasca dublu pointer, adica adresa acelui pointer
			inserareArbore(&arbore, e);
		}
		fclose(fp);
	}
	return arbore;
}

// moduri de parcurgere a arborelui, 3 moduri 
// - in ordine-subarobrele stanga, radacina -  subarborele drept- SRD(stanga, radacina, dreapta)
// - pre ordine-RSD
// - post ordine-SDR

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are un nr de %d medii, anume mediile: ", e.id, e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) 
	{
		printf("%5.2f", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrder(Nod* arbore) 
{
	if (arbore != NULL) {
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);
	}
}

float calculeazaMedieElev(Elev e) 
{
	if (e.nrMedii != 0) {
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++) 
		{
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else 
	{
		return 0;
	}
}

float calculeazaSumaNote(Nod* arbore, int* nrNote) 
{
	if (arbore != NULL) 
	{
		float suma = 0;

		// parcurg Radacina
		for (int i = 0; i < arbore->info.nrMedii; i++) 
		{
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii;
		// parcurg Stanga
		float sumaSt = calculeazaSumaNote(arbore->st, nrNote);
		// parcurg Dreapta
		float sumaDr = calculeazaSumaNote(arbore->dr, nrNote);

		return suma + sumaDr + sumaSt;
	}
	else
	{
		return 0;
	}
}

float calculeazaMediaGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	printf("\n Numarul de note %d \n", nrNote);
	if (nrNote > 0) {
		return suma / nrNote;
	}
	else {
		return 0;
	}
}

void main()
{
	// Declar arbore - il recunosc dupa adresa primului nod
	Nod* arbore = NULL;
	arbore = citireFisier("elevi.txt");
	afisareInOrder(arbore);
	printf("media este %5.2f \n", calculeazaMediaGenerala(arbore));
}


