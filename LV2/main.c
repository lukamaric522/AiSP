
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina;
    struct Osoba* sljedeci;
} Osoba;

void dodajNaPocetak(Osoba** glava) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska u memoriji.\n");
        return;
    }

    printf("Ime: ");
    scanf("%49s", nova->ime);

    printf("Prezime: ");
    scanf("%49s", nova->prezime);

    printf("Godina rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = *glava;
    *glava = nova;
}

void ispisiListu(Osoba* glava) {
    if (glava == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (glava != NULL) {
        printf("%s %s %d\n",
            glava->ime, glava->prezime, glava->godina);
        glava = glava->sljedeci;
    }
}

void dodajNaKraj(Osoba** glava) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    Osoba* trenutni;

    if (nova == NULL) {
        printf("Greska u memoriji.\n");
        return;
    }

    printf("Ime: ");
    scanf("%49s", nova->ime);

    printf("Prezime: ");
    scanf("%49s", nova->prezime);

    printf("Godina rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = NULL;

    if (*glava == NULL) {
        *glava = nova;
        return;
    }

    trenutni = *glava;

    while (trenutni->sljedeci != NULL) {
        trenutni = trenutni->sljedeci;
    }

    trenutni->sljedeci = nova;
}

Osoba* pronadiOsobu(Osoba* glava, char prezime[]) {
    while (glava != NULL) {
        if (strcmp(glava->prezime, prezime) == 0) {
            return glava;
        }

        glava = glava->sljedeci;
    }

    return NULL;
}

void obrisiOsobu(Osoba** glava, char prezime[]) {
    Osoba* trenutni = *glava;
    Osoba* prethodni = NULL;

    while (trenutni != NULL &&
        strcmp(trenutni->prezime, prezime) != 0) {
        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }

    if (trenutni == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    if (prethodni == NULL) {
        *glava = trenutni->sljedeci;
    }
    else {
        prethodni->sljedeci = trenutni->sljedeci;
    }

    free(trenutni);
    printf("Osoba je obrisana.\n");
}

void oslobodiListu(Osoba** glava) {
    Osoba* trenutni;

    while (*glava != NULL) {
        trenutni = *glava;
        *glava = (*glava)->sljedeci;
        free(trenutni);
    }
}

int main(void) {
    Osoba* glava = NULL;
    Osoba* pronadena;
    char prezime[50];
    int izbor;

    do {
        printf("\n1 - Dodaj na pocetak\n");
        printf("2 - Ispisi listu\n");
        printf("3 - Dodaj na kraj\n");
        printf("4 - Pronadi osobu\n");
        printf("5 - Obrisi osobu\n");
        printf("0 - Izlaz\n");
        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos.\n");
            oslobodiListu(&glava);
            return 1;
        }

        switch (izbor) {
        case 1:
            dodajNaPocetak(&glava);
            break;

        case 2:
            ispisiListu(glava);
            break;

        case 3:
            dodajNaKraj(&glava);
            break;

        case 4:
            printf("Unesite prezime: ");
            scanf("%49s", prezime);

            pronadena = pronadiOsobu(glava, prezime);

            if (pronadena != NULL) {
                printf("%s %s %d\n",
                    pronadena->ime,
                    pronadena->prezime,
                    pronadena->godina);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;

        case 5:
            printf("Unesite prezime za brisanje: ");
            scanf("%49s", prezime);
            obrisiOsobu(&glava, prezime);
            break;

        case 0:
            break;

        default:
            printf("Pogresan odabir.\n");
        }
    } while (izbor != 0);

    oslobodiListu(&glava);

    return 0;
}
