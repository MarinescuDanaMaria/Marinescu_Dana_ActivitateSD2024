#include <stdio.h>
#include <malloc.h>


typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct Nod {
    Biblioteca info;
    Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

//noi facem inserarea la inceputul listei
Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);//b.Ceva shallow copy IAR cu initializare(b.Ceva) am face deep copy
    nou->next = cap;
    return nou;
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        //procesare
        printf("Biblioteca %s are %d carti si %d cititori. \n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
        cap = cap->next;
    }
}
//fct de procesare care va determina numele bibliotecii cu cele mai multe carti per cititor
char* getBibliotecaNrCartiPerCititor(Nod* cap) {
    float max = 0;

    char* nume_aux = NULL;

    while (cap) {
        if (cap->info.nrCarti / cap->info.nrCititori > max) {
            max = cap->info.nrCarti / cap->info.nrCititori;
            nume_aux = cap->info.nume;
        }

        cap = cap->next;//delasarea
    }
    char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
    strcpy(nume, nume_aux);

    return nume;
}


void InserareLaSfarsit(Nod** cap, Biblioteca b) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));

    //initializam cele 2 atribute ale nodului sfarsit - info si next
    sfarsit->info = initializare(b.nume, b.nrCarti, b.nrCititori);
    sfarsit->next = NULL;


    if ((*cap) != NULL) {
        Nod* capA = (*cap);
        while (capA->next != NULL) {
            //intr-o lista parcurgerea se face secvential
            capA = capA->next;
        }

        capA->next = sfarsit; //pot face asa atribuire pt ca am acelasi tip compatibil
    }

    else {
        //deferentiem cap
        *cap = sfarsit;
    }

}


void stergeLista(Nod** cap) {
    while ((*cap) != NULL) {
        free((*cap)->info.nume);
        Nod* copie = *cap;
        *cap = (*cap)->next;

        free(copie);
    }
}


void main() {
   
    Nod* cap = NULL;

    Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
    cap = inserareInceput(cap, b1);

    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    cap = inserareInceput(cap, b2);

    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
    cap = inserareInceput(cap, b3);

    afisareLista(cap);
    
    /*cap = InserareInceput(cap, initializare("Mihai Eminescu", 150, 20));
    cap = InserareInceput(cap, initializare("Ioan Slavici", 200, 30));
    cap = InserareInceput(cap, initializare("Tudor Arghezi", 100, 15));*/
   
    char* numeDeAfisat = getBibliotecaNrCartiPerCititor(cap);
    printf("Biblioteca cu media maxima: %s \n\n\n", numeDeAfisat);
    free(numeDeAfisat);

    Biblioteca b4 = initializare("Radu Tudoran ", 100, 15);
    InserareLaSfarsit(&cap, b4);
    afisareLista(cap);

    stergeLista(&cap);
    afisareLista(cap);

    free(b1.nume);
    free(b2.nume);
    free(b3.nume);
    free(b4.nume);

}