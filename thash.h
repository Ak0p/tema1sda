#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

/* functii tabela hash */
TH* InitTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
int InsTH(TH*a, void*ae, TFCmp f, TFCmp e);

#endif
