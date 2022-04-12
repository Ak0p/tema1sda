/* BĂROIU Andrei - 312CB */
/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

int Ins_IncLG(TLG* aL, void* ae)
{
	TLG aux = (TLG)calloc(1,sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;

	return 1;
}

int InsLG(TLG *aL, void *ae) {
	TLG aux = (TLG)calloc(1, sizeof(TCelulaG));
	if(!aux)
			return 0;
	aux->info = ae;
	aux->urm = (*aL)->urm;
	(*aL)->urm = aux;
	return 1;

}

void DistrugeLG(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

void Afisare(TLG* aL, TF afiEL)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	printf("[\n");
	for(; *aL; aL = &(*aL)->urm) {
		afiEL((*aL)->info);
    }
	printf("]\n");
}
