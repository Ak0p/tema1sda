#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>
#define wordSize 25
#define lineSize 200



typedef struct {
  int lenght;
  TLG l;
} TMare;

typedef struct {
  int count;
  char *word;
} TMic;

TMic *alocMic(char*);
int cmpLen(void *, void *);
int cmpAlf(void *, void *);

int codHash(void * element) {
	char *cuvant = (char*) element;
  if ((*cuvant - 'A') < 26)
	 return *cuvant - 'A';
  else if ( ((*cuvant - 'a') < 26))
  return *cuvant - 'a';
  else {
    printf("Cod hash invalid\n");
    return -1;
  }
}

void AfiMic(TMic *cel) {
	printf("%s/%i", cel->word, cel->count);
}
void AfiMare(TMare *cel) {
	printf("(%i:", cel->lenght);
	TLG *u = &cel->l;
	for(; *u != NULL; *u = (*u)->urm) {
		AfiMic((TMic*)(*u)->info);
		if((*u)->urm)
			printf(", ");
	}
	if(!(*u)->urm)
		printf(")");
	else
		printf(") ");
}

void newAfiTH(TH* ah,TF afi_elem)
{
    TLG p, el;
    long unsigned i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("pos%lu: ",i);
            for(el = p; el != NULL; el = el->urm)
                AfiMare((TMare*)el->info);
            printf("\n");
        }
    }
}

int InserareEl(TH*a, void *ae, TFCmp fcmpAlf, TFCmp fcmpLen, TFHash fh) {
  char * cuvant = (char*)ae;
      printf("%s\n", cuvant);
  // TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
  // infocuv->word = (char*)calloc(1, strlen(cuvant));
  // infocuv->count = 1;
  // strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2

  if (!a->v[fh(cuvant)]) { // daca nu exista lista mare
    TMare *element = (TMare*)calloc(1, sizeof(TMare));
    element->lenght = (int)strlen(cuvant);
    element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
    if(!Ins_IncLG(&a->v[fh(cuvant)], (TMare*)element)) {
      return 0;
    }
    printf("Func 3\n");
    TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
    infocuv->word = (char*)calloc(1, strlen(cuvant));
    infocuv->count = 1;
    strcpy(infocuv->word, cuvant);
    TMare * pointerUseless = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru lista #2
    if(!Ins_IncLG(&(pointerUseless->l), (TMic*)infocuv)) {
      pointerUseless = NULL;
      return 0;
    }
    pointerUseless = NULL;
    return 1;
  }
  TLG p = a->v[fh(cuvant)];
  for(; p != NULL; p = p->urm) {
    TMare *ponterMare = (TMare*)(p->info);
    if (ponterMare->lenght < (int)strlen(cuvant)) {
      printf("Func 5?\n");
      if(p->urm) {
        ponterMare = (TMare*)p->urm->info;
        if(ponterMare->lenght <= (int)strlen(cuvant))
          continue;
      }
      else {
        printf("Func 6.5?\n");
        TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
        infocuv->word = (char*)calloc(1, strlen(cuvant));
        infocuv->count = 1;
        strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
        TMare *element = (TMare*)calloc(1, sizeof(TMare));
        element->lenght = strlen(infocuv->word);
        element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
        if(!Ins_IncLG(&element->l, infocuv))
          return 0;
        if(!InsLG(&p, element))
          return 0;
        return 1;
      }

    } else if ((long unsigned)ponterMare->lenght == strlen(cuvant)) {

      signed char val = 0;
      TLG u = (TLG)ponterMare->l;
      for(; u != NULL; u = u->urm) {
        TMic *ponterMic = (TMic*)(u->info);
        if(strcmp(ponterMic->word, cuvant) == 0) {
          val = 1;
          ponterMic->count++;
          return 1;
        }
      }
      printf("Func 8?\n");
      if (val == 0) {
        TMic *infocuv = alocMic(cuvant);
        if(!InsLG(&u, infocuv))
          return 0;
      }
      return 1;

    } else {
      printf("Func 9?\n");
      TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
      infocuv->word = (char*)calloc(1, strlen(cuvant));
      infocuv->count = 1;
      strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
      TMare *element = (TMare*)calloc(1, sizeof(TMare));
      element->lenght = strlen(infocuv->word);
      element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
      if(!Ins_IncLG(&element->l, infocuv))
        return 0;
      if(!Ins_IncLG(&p, element))
        return 0;
      return 1;
    }
  }
  return 1;
}


TMic *alocMic(char * cuvant) {
  TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
  infocuv->word = (char*)calloc(1, strlen(cuvant));
  infocuv->count = 1;
  strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
  return infocuv;
}


void afisareElement(void * element) {

}

// int cmpCarte(void * e1, void * e2)
// {
// 	TZInfo * info1 = (TZInfo *) e1;
// 	TZInfo * info2 = (TZInfo *) e2;
//
// 	if (strcmp(carte1->titlu, carte2->titlu) != 0)
// 		return 0;
//
// 	if (strcmp(carte1->autor, carte2->autor) != 0)
// 		return 0;
//
// 	if (strcmp(carte1->editura, carte2->editura) != 0)
// 		return 0;
//
// 	return 1;
// }

int cmpLen(void * e1, void * e2) {
	TMic * info1 = (TMic *) e1;
	TMic * info2 = (TMic *) e2;

	if (strlen(info1) - strlen(info2) != 0)
		return 0;

	return 1;
}

int cmpAlf(void * e1, void * e2)
{
	TMic * info1 = (TMic *) e1;
	TMic * info2 = (TMic *) e2;
	if (strcmp(info1->word, info2->word) != 0) {
  printf("cccccc\n");
		return 0;
    }
	return 1;
}

TH * oldGenerareHash(TLG listacuvinte) {
    TH *h = NULL;
	TLG p;
    TMare * el;
	int rez;

	/* calcul dimensiuni maxime pt tabela hash */
	size_t M = ('Z'-'A');

	/* initializare tabela hash */
	h = (TH *) InitTH(M, codHash);
	if(h == NULL)
		return NULL;

	for(p = listacuvinte; p != NULL; p = p->urm) {
        el = (TMare *) malloc(sizeof(TMare));
        if(el == NULL)
						return h;

        memcpy(el, p->info, sizeof(TMare));
		rez = InserareEl(h, el, cmpLen, cmpAlf, codHash);
        if(!rez) {
						free(el);
						return h;
		}
	}
  return h;
}

TH * GenerareHash() {
    TH *h = NULL;
	TLG p;
    TMare * el;
	int rez;

	/* calcul dimensiuni maxime pt tabela hash */
	size_t M = ('Z'-'A');

	/* initializare tabela hash */
	h = (TH *) InitTH(M, codHash);
	if(h == NULL)
		return NULL;

    for(int i = 0; i < (int)M; i++) {
      h->v[i] = NULL;
    }
  return h;
}

int bobelsort(TLG *l) {
  TLG p = *l, ant = *l, aux;
  int ok = 0;
  while(!ok) {
    ant = *l;
    p = *l;
    for(;p != NULL && p->urm != NULL; p = p->urm) {
      if(ant == p)
        continue;
      else
        ant->urm = p;
      if((int)(p->(TMic*)(info)->count) < (int)(p->urm->(TMic*)(info)->count))) {

        ant->urm = p->urm;
        aux = p->urm->urm;
        p->urm->urm = p;
        p->urm = aux;

      } else if (p->info->count > p->info->urm->count)  // castari????
        ok = 1;
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {
  TH h;
  h = *InitTH('Z' - 'A', codHash);
  FILE *input;
  input = fopen(argv[1], "r");

  while(1) {
    // start citire & prelucrare comanda
    char *comanda = (char*)calloc(lineSize, sizeof(char));
    char **cuvant = (char**)calloc(wordSize, sizeof(char*));
    int contor1 = 0;
    if(!fgets(comanda, lineSize, input)) {
      fclose(input);
      return 0;
    }
    cuvant[contor1] = strtok(comanda, " .,\n");
    while (cuvant[contor1]) {
      // printf("%d - %s\n", contor1, cuvant[contor1]);
      contor1++;
      cuvant[contor1] = strtok(NULL, " .,\n");
      // end citire & prelucrare comanda
      // start insert block
      if (strcmp(cuvant[0], "insert") == 0) {
          if(strlen(cuvant[contor1]) < 3)
            continue;

          if(!InserareEl(&h, cuvant[contor1], cmpAlf, cmpLen, codHash)) {
            printf("Inserare nereușita\n");
            return -1;
          }
      }
    }


      // end insert block
      // start print block

      if (strcmp(cuvant[0], "print") == 0) {
        continue;
      }

    }
    fclose(input);
    return 0;
  }