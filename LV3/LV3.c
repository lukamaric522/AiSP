
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

void unesiOsobu(Osoba* nova) {
    printf("Ime: ");
    scanf("%49s", nova->ime);

    printf("Prezime: ");
    scanf("%49s", nova->prezime);

    printf("Godina rodenja: ");
    scanf("%d", &nova->godina);
}

void dodajNaPocetak(Osoba** glava) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska u memoriji.\n");
        return;
    }

    unesiOsobu(nova);

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

    unesiOsobu(nova);
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

void dodajIzaOsobe(Osoba* glava, char prezime[]) {
    Osoba* trenutni = pronadiOsobu(glava, prezime);
    Osoba* nova;

    if (trenutni == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska u memoriji.\n");
        return;
    }

    unesiOsobu(nova);

    nova->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = nova;

    printf("Osoba je dodana iza odabrane osobe.\n");
}

void dodajIspredOsobe(Osoba** glava, char prezime[]) {
    Osoba* trenutni = *glava;
    Osoba* prethodni = NULL;
    Osoba* nova;

    while (trenutni != NULL &&
        strcmp(trenutni->prezime, prezime) != 0) {
        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }

    if (trenutni == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska u memoriji.\n");
        return;
    }

    unesiOsobu(nova);

    nova->sljedeci = trenutni;

    if (prethodni == NULL) {
        *glava = nova;
    }
    else {
        prethodni->sljedeci = nova;
    }

    printf("Osoba je dodana ispred odabrane osobe.\n");
}

void sortirajListu(Osoba** glava) {
    Osoba* i, * j, * prev, * temp;
    int zamjena;

    if (*glava == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    do {
        zamjena = 0;
        prev = NULL;
        i = *glava;

        while (i != NULL && i->sljedeci != NULL) {
            j = i->sljedeci;

            if (strcmp(i->prezime, j->prezime) > 0) {
                i->sljedeci = j->sljedeci;
                j->sljedeci = i;

                if (prev == NULL) {
                    *glava = j;
                }
                else {
                    prev->sljedeci = j;
                }

                prev = j;
                zamjena = 1;
            }
            else {
                prev = i;
                i = i->sljedeci;
            }
        }
    } while (zamjena);

    printf("Lista je sortirana po prezimenima.\n");
}

void upisiUDatoteku(Osoba* glava) {
    FILE* datoteka = fopen("osobe.txt", "w");

    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    while (glava != NULL) {
        if (fprintf(datoteka, "%s %s %d\n",
            glava->ime, glava->prezime, glava->godina) < 0) {
            printf("Greska pri upisu u datoteku.\n");
            fclose(datoteka);
            return;
        }

        glava = glava->sljedeci;
    }

    if (fclose(datoteka) != 0) {
        printf("Greska pri zatvaranju datoteke.\n");
        return;
    }

    printf("Lista je upisana u datoteku osobe.txt.\n");
}

void ucitajIzDatoteke(Osoba** glava) {
    FILE* datoteka = fopen("osobe.txt", "r");
    Osoba* nova;
    Osoba* zadnji = NULL;
    char ime[50];
    char prezime[50];
    int godina;
    int rezultat;

    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke osobe.txt.\n");
        return;
    }

    while (1) {
        rezultat = fscanf(datoteka, "%49s %49s %d",
            ime, prezime, &godina);

        if (rezultat == EOF) {
            break;
        }

        if (rezultat != 3) {
            printf("Neispravan format datoteke.\n");
            fclose(datoteka);
            return;
        }

        nova = (Osoba*)malloc(sizeof(Osoba));

        if (nova == NULL) {
            printf("Greska u memoriji.\n");
            fclose(datoteka);
            return;
        }

        strcpy(nova->ime, ime);
        strcpy(nova->prezime, prezime);
        nova->godina = godina;
        nova->sljedeci = NULL;

        if (*glava == NULL) {
            *glava = nova;
        }
        else {
            zadnji->sljedeci = nova;
        }

        zadnji = nova;
    }

    fclose(datoteka);
    printf("Lista je ucitana iz datoteke osobe.txt.\n");
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
        printf("6 - Dodaj iza odabrane osobe\n");
        printf("7 - Dodaj ispred odabrane osobe\n");
        printf("8 - Sortiraj po prezimenima\n");
        printf("9 - Upisi listu u datoteku\n");
        printf("10 - Ucitaj listu iz datoteke\n");
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

        case 6:
            printf("Prezime osobe iza koje se dodaje nova osoba: ");
            scanf("%49s", prezime);
            dodajIzaOsobe(glava, prezime);
            break;

        case 7:
            printf("Prezime osobe ispred koje se dodaje nova osoba: ");
            scanf("%49s", prezime);
            dodajIspredOsobe(&glava, prezime);
            break;

        case 8:
            sortirajListu(&glava);
            break;

        case 9:
            upisiUDatoteku(glava);
            break;

        case 10:
            ucitajIzDatoteke(&glava);
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
