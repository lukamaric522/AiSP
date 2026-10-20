
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Osoba {
    char ime[20];
    char prezime[20];
    int bodovi;
};

int main(void) {
    FILE* s = NULL;
    int brojOsoba = 0;
    int max_br_bodova = 20;
    char temp[100];

    s = fopen("Osobe.txt", "r");

    if (s == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    while (fgets(temp, sizeof(temp), s) != NULL) {
        brojOsoba++;
    }

    fclose(s);

    struct Osoba* o = malloc(brojOsoba * sizeof(struct Osoba));

    if (o == NULL && brojOsoba > 0) {
        printf("Greska pri alokaciji memorije!\n");
        return 1;
    }

    s = fopen("Osobe.txt", "r");

    if (s == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        free(o);
        return 1;
    }

    int i = 0;

    while (i < brojOsoba &&
        fscanf(s, "%19s %19s %d",
            o[i].ime, o[i].prezime, &o[i].bodovi) == 3) {
        i++;
    }

    fclose(s);

    for (int j = 0; j < i; j++) {
        float relativni_bodovi =
            (o[j].bodovi / (float)max_br_bodova) * 100;

        printf("%s %s A: %d, R: %.2f%%\n",
            o[j].ime,
            o[j].prezime,
            o[j].bodovi,
            relativni_bodovi);
    }

    free(o);

    return 0;
}
