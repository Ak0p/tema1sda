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

// int MegaIns(TH *a, void* ae, TFCmp fcmpAlf, TFCmp fcmpLen, TFHash fh) {
//   char * cuvant = (char*)ae;
//   TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
//   infocuv->word = (char*)calloc(1, strlen(cuvant));
//   infocuv->count = 1;
//   strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
//   if (!a->v[fh(cuvant)]->urm) {
//
//     // daca nu exista un element in lista #1 adaug unul cu lenght strlen(infocuv.word)
//
//     TMare *element = (TMare*)calloc(1, sizeof(TMare));
//     element->lenght = strlen(infocuv->word);
//     element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
//     if (!Ins_IncLG(&element->l, &infocuv)) {
//       printf("Eroare alocare element_2\n");
//       return 0;
//     }  // asociere cel lista #2 cu info lista #1
//     // a->v[fh(cuvant)] = element.l;
//     if (!Ins_IncLG(&a->v[fh(cuvant)], &element)) {
//       printf("Eroare alocare element_1\n");
//       return 0;
//     }   // alocare celula prelucrata in lista #1
//     return 1;
//   } else {
//     TLG *p = &a->v[fh(cuvant)];
//     TLG *u = NULL;
//     for(;(*p) != NULL || (*p)->info->lenght > element->lenght ; (*p) = (*p)->urm) {
//       // iterez print elementele listei #1 pentru a gasi elementul cu lungimea <= cu a infocuv.word
//       if(*p->urm) {  // daca exista urmatorul element si strlen(infocuv.word se afla in intervalul deschis dintre celule adaug o noua celula)
//         if (element->lenght > *p->info->lenght && element->lenght < *p->urm->info->lenght) {
//           if (!Ins_IncLG(p->l, &infocuv)) {
//             printf("Eroare alocare element_2\n");
//             return 0;
//           }  // asociere cel lista #2 cu info lista #1
//
//        }
//      } else if (element.lenght == (*p)->info->lenght) {
//       u = (*p)->info->l;
//       for(;u != NULL; u = u->urm) {
//         if (strcmp(infocuv.word, *u->info->word) == 0) {
//           *u->info->count++;
//         } else {
//           Ins_IncLG(&u, infocuv);
//         }
//       }
//     }
//     }
//   }
// }

int InserareEl(TH*a, void *ae, TFCmp fcmpAlf, TFCmp fcmpLen, TFHash fh) {
  char * cuvant = (char*)ae;
  // TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
  // infocuv->word = (char*)calloc(1, strlen(cuvant));
  // infocuv->count = 1;
  // strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2

  if (!a->v[fh(cuvant)]->urm) { // daca nu exista lista mare
    TMare *element = (TMare*)calloc(1, sizeof(TMare));
    element->lenght = strlen(cuvant);
    element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
    if(!Ins_IncLG(&a->v[fh(cuvant)], element)) {
      return 0;
    }
    TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
    infocuv->word = (char*)calloc(1, strlen(cuvant));
    infocuv->count = 1;
    strcpy(infocuv->word, cuvant);
    TMare * pointerUseless = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru lista #2
    if(!Ins_IncLG(&(pointerUseless->l), infocuv)) {
      pointerUseless = NULL;
      return 0;
    }
    pointerUseless = NULL;
    return 1;
  }
  TLG *p = (TLG*)a->v[fh(cuvant)];
  for(; (*p) != NULL; (*p) = (*p)->urm) {
    TMare *ponterMare = (TMare*)(*p)->info;
    if ((long unsigned)ponterMare->lenght < strlen(cuvant)) {
      ponterMare = (TMare*)(*p)->urm->info;
      if((*p)->urm && (long unsigned)ponterMare->lenght <= strlen(cuvant))
        continue;
      else {
        TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
        infocuv->word = (char*)calloc(1, strlen(cuvant));
        infocuv->count = 1;
        strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
        TMare *element = (TMare*)calloc(1, sizeof(TMare));
        element->lenght = strlen(infocuv->word);
        element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
        if(!Ins_IncLG(&element->l, infocuv))
          return 0;
        if(!InsLG(p, element))
          return 0;
        return 1;
      }

    } else if ((long unsigned)ponterMare->lenght == strlen(cuvant)) {
      signed char val = 0;
      TLG *u = &ponterMare->l;
      for(; (*u) != NULL; (*u) = (*u)->urm) {
        TMic *ponterMic = (TMic*)(*u)->info;
        if(fcmpAlf(ponterMic->word, cuvant) == 0) {
          val = 1;
          ponterMic->count++;
          return 1;
        }
      }
      if (val == 0) {
        TMic *infocuv = alocMic(cuvant);
        if(!InsLG(u, infocuv))
          return 0;
      }
      return 1;

    } else {
      TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
      infocuv->word = (char*)calloc(1, strlen(cuvant));
      infocuv->count = 1;
      strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
      TMare *element = (TMare*)calloc(1, sizeof(TMare));
      element->lenght = strlen(infocuv->word);
      element->l = (TLG)calloc(1, sizeof(TLG));  // alocare info lista #!
      if(!Ins_IncLG(&element->l, infocuv))
        return 0;
      if(!Ins_IncLG(p, element))
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
	char * info1 = (char *) e1;
	char * info2 = (char *) e2;

	if (strlen(info1) - strlen(info2) != 0)
		return 0;

	return 1;
}

int cmpAlf(void * e1, void * e2)
{
	TMic * info1 = (TMic *) e1;
	TMic * info2 = (TMic *) e2;

	if (strcmp(info1->word, info2->word) != 0)
		return 0;
	return 1;
}

TH * GenerareHash(TLG listacuvinte) {
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

int main(int argc, char *argv[]) {
  //InitTH('Z' - 'A' + 1, codHash);
  FILE *input;

  input = fopen(argv[1], "r");

  while(1) {
    // start citire & prelucrare comanda
    char *comanda = (char*)calloc(lineSize, sizeof(char));
    char **cuvant = (char**)calloc(wordSize, sizeof(char*));
    int contor1 = 0;
    if(!fgets(comanda, lineSize, input))
      return 0;
    cuvant[contor1] = strtok(comanda, " .,\n");
    while (cuvant[contor1]) {
      printf("%d - %s\n", contor1, cuvant[contor1]);
      contor1++;
      cuvant[contor1] = strtok(NULL, " .,\n");
      // end citire & prelucrare comanda
      // start insert block
      if (strcmp(cuvant[0], "insert") == 0) {
        // int i = 1;
        // while(cuvant[i]) {
        //   if(strlen(cuvant[i]) <= 3)
        //     continue;
        //     //if()
        //   i++;
        // }
      }

      // end insert block
      // start print block

      if (strcmp(cuvant[0], "print") == 0) {
        continue;
      }

    }

  }
  fclose(input);
  return 0;
}
