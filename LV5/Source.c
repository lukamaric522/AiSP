
#include <stdio.h>
#include <stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;

struct _Cvor
{
    int Element;
    Position Next;
};

void ReadListFromFile(Position);
void PrintList(Position);
void Presjek(Position, Position, Position);
void Unija(Position, Position, Position);
void DeleteList(Position);

int main(void)
{
    Position headL1, headL2, headP, headU;

    headL1 = (Position)malloc(sizeof(struct _Cvor));
    if (headL1 == NULL) return 1;
    headL1->Next = NULL;

    headL2 = (Position)malloc(sizeof(struct _Cvor));
    if (headL2 == NULL) return 1;
    headL2->Next = NULL;

    headP = (Position)malloc(sizeof(struct _Cvor));
    if (headP == NULL) return 1;
    headP->Next = NULL;

    headU = (Position)malloc(sizeof(struct _Cvor));
    if (headU == NULL) return 1;
    headU->Next = NULL;

    ReadListFromFile(headL1);
    ReadListFromFile(headL2);

    printf("\nLista L1 :");
    PrintList(headL1->Next);

    printf("\nLista L2 :");
    PrintList(headL2->Next);

    Presjek(headL1->Next, headL2->Next, headP);
    printf("\nPresjek L1 i L2 je :");
    PrintList(headP->Next);

    Unija(headL1->Next, headL2->Next, headU);
    printf("\nUnija L1 i L2 je :");
    PrintList(headU->Next);

    printf("\n");

    DeleteList(headL1);
    DeleteList(headL2);
    DeleteList(headP);
    DeleteList(headU);

    return 0;
}

void ReadListFromFile(Position P)
{
    FILE* stream;
    char ime_dat[1024];
    Position q, tmp;

    printf("\nUnesite ime datoteke za citanje : ");
    scanf_s("%1023s", ime_dat, (unsigned)sizeof(ime_dat));

    fopen_s(&stream, ime_dat, "r");

    if (stream == NULL)
    {
        printf("\nGreska!\nDatoteka: %s nije otvorena.", ime_dat);
    }
    else
    {
        int broj;

        while (fscanf_s(stream, "%d", &broj) == 1)
        {
            q = (Position)malloc(sizeof(struct _Cvor));

            if (q == NULL)
            {
                printf("\nGreska!\nMemorija nije alocirana.");
                break;
            }

            q->Element = broj;

            tmp = P;

            while (tmp->Next != NULL &&
                tmp->Next->Element > q->Element)
            {
                tmp = tmp->Next;
            }

            q->Next = tmp->Next;
            tmp->Next = q;
        }

        fclose(stream);
    }
}

void PrintList(Position P)
{
    while (P != NULL)
    {
        printf(" %d", P->Element);
        P = P->Next;
    }
}

void Presjek(Position L1, Position L2, Position P)
{
    Position q;

    while (L1 != NULL && L2 != NULL)
    {
        if (L1->Element > L2->Element)
            L1 = L1->Next;

        else if (L1->Element < L2->Element)
            L2 = L2->Next;

        else
        {
            q = (Position)malloc(sizeof(struct _Cvor));

            if (q == NULL)
            {
                printf("\nGreska!\nMemorija nije alocirana.");
                return;
            }

            q->Element = L1->Element;

            q->Next = P->Next;
            P->Next = q;

            P = q;

            L1 = L1->Next;
            L2 = L2->Next;
        }
    }
}

void Unija(Position L1, Position L2, Position U)
{
    Position q, tmp;
    int tmp_element;

    while (L1 != NULL && L2 != NULL)
    {
        if (L1->Element > L2->Element)
        {
            tmp_element = L1->Element;
            L1 = L1->Next;
        }
        else if (L1->Element < L2->Element)
        {
            tmp_element = L2->Element;
            L2 = L2->Next;
        }
        else
        {
            tmp_element = L1->Element;
            L1 = L1->Next;
            L2 = L2->Next;
        }

        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
        {
            printf("\nGreska!\nMemorija nije alocirana.");
            return;
        }

        q->Element = tmp_element;

        q->Next = U->Next;
        U->Next = q;

        U = q;
    }

    if (L1 == NULL)
        tmp = L2;
    else
        tmp = L1;

    while (tmp != NULL)
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
        {
            printf("\nGreska!\nMemorija nije alocirana.");
            return;
        }

        q->Element = tmp->Element;

        q->Next = U->Next;
        U->Next = q;

        U = q;

        tmp = tmp->Next;
    }
}

void DeleteList(Position P)
{
    Position tmp;

    while (P != NULL)
    {
        tmp = P;
        P = P->Next;
        free(tmp);
    }
}
