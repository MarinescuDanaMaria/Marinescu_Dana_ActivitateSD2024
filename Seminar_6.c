// SEMINAR 6 - LISTE DUBLU INLANTUITE

// dezav - ocupa mai mult - pointeri suplim
//       - Avem mai multe legaturi si putem gresi usor 


// creem o structura care sa retina cele 2 adrese (  pt a putea parvurge de la inceput la sf si invers
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


// tema sa inseram un nod in int listei

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Biblioteca
{
    char* nume;
    int nrCarti;
    int nrCititori;

};

struct Nod
{
    Biblioteca info;
    Nod* next;
    Nod* prev;
};

struct ListaDubla
{
    Nod* head;
    Nod* tail;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori)
{
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

void inserareInceput(ListaDubla* listaDubla, Biblioteca b)
{
    Nod* nod = (Nod*)malloc(sizeof(Nod)); // alocam spatiu pe heap, de aia e pointer 
    nod->info = b;
    nod->next = listaDubla->head;
    nod->prev = NULL;

    // daca aveam inserare la sf 
    /*nod->next = NULL;
    nod->prev = listaDubla->tail;*/
    if (listaDubla->head)
    {
        listaDubla->head->prev = nod;
    }
    else
    {
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
}

void afisareListaInceput(ListaDubla listaDubla)
{
    while (listaDubla.head)
    {
        printf("Biblioteca: %s Nr cititori: %d Nr carti: %d\n", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
        listaDubla.head = listaDubla.head->next;
    }
    printf("\n");
}

void stergeNodNume(ListaDubla* listaDubla, const char* nume)
{
    Nod* aux = listaDubla->head;
    while (aux && strcmp(nume, aux->info.nume) != 0) // iese din while cand gaseste numele sau la final
    {
        aux = aux->next;

    }
    if (aux)
    {
        if (aux == listaDubla->head) // nodul de la inceput
        {
            if (aux == listaDubla->tail)
            {
                listaDubla->head = NULL;
                listaDubla->tail = NULL;
            }
            else
            {
                listaDubla->head = listaDubla->head->next;
                listaDubla->head->prev = NULL;
            }

        }
        else  // ESTE LA SFARSIT
        {
            if (aux == listaDubla->tail)
            {
                aux->prev->next = NULL;
                listaDubla->tail = aux->prev;
            }
            else // este in interior
            {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
        }
        free(aux->info.nume);
        free(aux);


    }
}

void stergereLista(ListaDubla* listaDubla) // o modif de aia e prin * 
{
    while (listaDubla->head)
    {
        free(listaDubla->head->info.nume);
        Nod* aux = listaDubla->head;
        listaDubla->head = listaDubla->head->next;
        free(aux);


    }

    listaDubla->head = NULL;
    listaDubla->tail = NULL;
}

int nrCartiTotal(ListaDubla  listaDubla)
{
    int rezultat = 0;
    while (listaDubla.tail)
    {
        rezultat += listaDubla.tail->info.nrCarti;
        listaDubla.tail = listaDubla.tail->prev;
    }
    return rezultat;
}







void main()
{

    Biblioteca b1 = initializare("Mihai Eminescu", 150, 30);
    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);

    ListaDubla listaDubla; // obiect 
    // la inc, init pointerii cu null
    listaDubla.head = NULL;
    listaDubla.tail = NULL;

    inserareInceput(&listaDubla, b1);
    inserareInceput(&listaDubla, b2);
    inserareInceput(&listaDubla, b3);

    afisareListaInceput(listaDubla);

    int rezultat = nrCartiTotal(listaDubla);
    printf("Nr tot carti : %d ", rezultat);

    /* stergeNodNume(&listaDubla, "Ioan Slavici");
     afisareListaInceput(listaDubla);

     stergeNodNume(&listaDubla, "Mihai Eminescu");
     afisareListaInceput(listaDubla);

     stergeNodNume(&listaDubla, "Tudor Arghezi");
     afisareListaInceput(listaDubla);*/

    stergereLista(&listaDubla);
    afisareListaInceput(listaDubla);





}