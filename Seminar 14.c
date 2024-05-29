#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Metrou Metrou;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Metrou {
	int serie;
	int nrStatie;
	char* magistrala;
};

struct NodPrincipal {
	Metrou info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie initializare metrou

Metrou creareMetrou(int serie, int nrStatii, const char* magistrala) {
	Metrou m;
	m.serie = serie;
	m.nrStatie = nrStatii;
	m.magistrala = (char*)malloc(sizeof(char) * (strlen(magistrala) + 1));
	strcpy(m.magistrala, magistrala);
	return m;
}


//inserare la inceput in lista principala

void inserarePrincipala(NodPrincipal** cap, Metrou m) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}


//functie cautare nod dupa serie

NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}


//inserare la final in lista secundara

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = nod;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}


//functie inserare muchie

void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
	}
}


//pragma e doar pt estetica ca sa putem restrange codul
#pragma region Coada
//definim regiune coada
typedef struct NodCoada NodCoada;
struct NodCoada {
	int serie;
	NodCoada* next;
};

//inserare si extragere trebuie sa fim atenti sa avem coada
//TREBUIE SA FIE OPUSE INSERAREA SI EXTRAGEREA pt coada
//adica daca inserare se face final atunci extragerea la inceput
//inserare la final
void inserareCoada(NodCoada** cap, int serie) {
	NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
	nodNou->serie = serie;
	nodNou->next = NULL;
	if (*cap) {
		NodCoada* aux=(*cap);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nodNou;

	}
	else {
		*cap = nodNou;
	}
}

//extragere la inceput, e extras cap DOAR daca exista coada
int extragereCoada(NodCoada** cap) {
	if (*cap) {
		int rezultat = (*cap)->serie;
		//stergem primul nod
		NodCoada* aux = (*cap);
		*cap = aux->next;//sau *cap = (*cap)->next; 
		free(aux);
		return rezultat;
	}
	else return -1;
}
#pragma endregion


int getnumarNoduri(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}


void afisareMetrou(Metrou m) {
	printf("%d. numar statii: %d   magistrala: %s \n", m.serie, m.nrStatie, m.magistrala);
}

//afisare prin parcurgere in latime
void afisareParcurgereInLatime(NodPrincipal* graf, int serie) {
	if (graf) {
		NodCoada* coada = NULL;
		int nrNoduri = getnumarNoduri(graf);
		char* vizitate = (char*)malloc(nrNoduri); //char ocupa mai putin spatiu decat int

		for (int i = 0; i < nrNoduri; i++) {
			vizitate[i] = 0;
		}

		inserareCoada(&coada, serie);
		//marcam vectorul de vizitate
		vizitate[serie] = 1;

		//acum incepem procesul repetitiv, luam din coada, inseram vecinii 
		while (coada) {
			int serieNoua = extragereCoada(&coada);
			NodPrincipal* nou = cautaNodDupaSerie(graf, serieNoua);
			afisareMetrou(nou->info);

			//ii aflam vecinii, parcurgem nodurile secundare ale lui nou
			NodSecundar* temp = nou->vecini;
			while (temp) {
				if (vizitate[temp->nod->info.serie] == 0) {
					vizitate[temp->nod->info.serie] = 1;
					inserareCoada(&coada, temp->nod->info.serie);

				}
				temp = temp->next;
				//consideram ca avem o singura componenta conexa

			}
		}
		if (vizitate) {
			free(vizitate);
		}
	}
}

void stergeVecini(NodSecundar** vecini) {
	while (*vecini) {
		NodSecundar* temp = *vecini;
		*vecini = temp->next;
		free(temp);
	}
}

//functie dezalocare
void dezalocareGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* aux = *graf;
		free(aux->info.magistrala);

		stergeVecini(&(aux->vecini));

		*graf = aux->next;
		free(aux);
	}
}


void main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, creareMetrou(4, 6, "M2"));
	inserarePrincipala(&graf, creareMetrou(3, 7, "M1"));
	inserarePrincipala(&graf, creareMetrou(2, 8, "M4"));
	inserarePrincipala(&graf, creareMetrou(1, 12, "M5"));
	inserarePrincipala(&graf, creareMetrou(0, 4, "M6"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);

	afisareParcurgereInLatime(graf, 0);

	dezalocareGraf(&graf);

}