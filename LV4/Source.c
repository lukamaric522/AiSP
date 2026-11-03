
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;

struct _Cvor
{
    int Koeficijent;
    int Exponent;
    Position Next;
};

void ReadPolynom(Position P);
void PrintPolynom(Position P);
void SumPolynom(Position P, Position Q, Position S);
void MulPolynom(Position P, Position Q, Position M);
void InsertSorted(Position P, int koef, int exp);

int main(void)
{
    struct _Cvor P, Q, S, M;

    P.Next = NULL;
    Q.Next = NULL;
    S.Next = NULL;
    M.Next = NULL;

    ReadPolynom(&P);
    ReadPolynom(&Q);

    printf("\nP(x) = ");
    PrintPolynom(P.Next);

    printf("Q(x) = ");
    PrintPolynom(Q.Next);

    SumPolynom(P.Next, Q.Next, &S);

    printf("\nS(x) = P(x) + Q(x) = ");
    PrintPolynom(S.Next);

    MulPolynom(P.Next, Q.Next, &M);

    printf("\nM(x) = P(x) * Q(x) = ");
    PrintPolynom(M.Next);

    printf("\n");

    return 0;
}

void InsertSorted(Position P, int koef, int exp)
{
    Position q, i;

    if (koef == 0)
        return;

    i = P;

    while (i->Next != NULL &&
        i->Next->Exponent > exp)
    {
        i = i->Next;
    }

    if (i->Next != NULL &&
        i->Next->Exponent == exp)
    {
        i->Next->Koeficijent += koef;

        if (i->Next->Koeficijent == 0)
        {
            q = i->Next;
            i->Next = q->Next;
            free(q);
        }
    }
    else
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
            return;

        q->Koeficijent = koef;
        q->Exponent = exp;

        q->Next = i->Next;
        i->Next = q;
    }
}

void ReadPolynom(Position P)
{
    char ime_dat[1024];
    FILE* stream;
    int koef, exp;

    printf("\nUnesite ime datoteke za citanje polinoma: ");

    if (scanf("%1023s", ime_dat) != 1)
        return;

    stream = fopen(ime_dat, "r");

    if (stream == NULL)
    {
        printf("\nGreska! Datoteka %s nije otvorena.\n",
            ime_dat);
        return;
    }

    while (fscanf(stream, "%d %d", &koef, &exp) == 2)
    {
        InsertSorted(P, koef, exp);
    }

    fclose(stream);
}

void PrintPolynom(Position P)
{
    int first = 1;
    long long koef;

    if (P == NULL)
    {
        printf("0\n");
        return;
    }

    while (P != NULL)
    {
        koef = P->Koeficijent;

        if (first)
        {
            if (koef < 0)
                printf("-");

            if (koef < 0)
                koef = -koef;
        }
        else
        {
            if (koef > 0)
                printf(" + ");
            else
            {
                printf(" - ");
                koef = -koef;
            }
        }

        if (P->Exponent == 0)
        {
            printf("%lld", koef);
        }
        else
        {
            if (koef != 1)
                printf("%lld", koef);

            if (P->Exponent > 0)
                printf("x^%d", P->Exponent);
            else
                printf("x^(%d)", P->Exponent);
        }

        first = 0;
        P = P->Next;
    }

    printf("\n");
}

void SumPolynom(Position P, Position Q, Position S)
{
    Position q;
    Position tail = S;

    while (P != NULL && Q != NULL)
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
            return;

        if (P->Exponent > Q->Exponent)
        {
            q->Exponent = P->Exponent;
            q->Koeficijent = P->Koeficijent;

            P = P->Next;
        }
        else if (P->Exponent < Q->Exponent)
        {
            q->Exponent = Q->Exponent;
            q->Koeficijent = Q->Koeficijent;

            Q = Q->Next;
        }
        else
        {
            q->Exponent = P->Exponent;
            q->Koeficijent =
                P->Koeficijent + Q->Koeficijent;

            P = P->Next;
            Q = Q->Next;
        }

        if (q->Koeficijent == 0)
        {
            free(q);
        }
        else
        {
            q->Next = NULL;
            tail->Next = q;
            tail = q;
        }
    }

    while (P != NULL || Q != NULL)
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
            return;

        if (P != NULL)
        {
            q->Koeficijent = P->Koeficijent;
            q->Exponent = P->Exponent;
            P = P->Next;
        }
        else
        {
            q->Koeficijent = Q->Koeficijent;
            q->Exponent = Q->Exponent;
            Q = Q->Next;
        }

        q->Next = NULL;
        tail->Next = q;
        tail = q;
    }
}

void MulPolynom(Position P, Position Q, Position M)
{
    Position i, j;

    i = P;

    while (i != NULL)
    {
        j = Q;

        while (j != NULL)
        {
            InsertSorted(
                M,
                i->Koeficijent * j->Koeficijent,
                i->Exponent + j->Exponent
            );

            j = j->Next;
        }

        i = i->Next;
    }
}
