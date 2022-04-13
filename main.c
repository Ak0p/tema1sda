/* BĂROIU Andrei - 312CB */
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
void AfiMic(TMic*, int);
void AfiMare(TMare*, int);
void newAfiTH(TH*, int, int, int);
void bobelsort(TLG *);
void swap(TLG, TLG);


int codHash(void * element) {  /*functia determina codul hash dintr-un string*/
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

void AfiMic(TMic *cel, int argument2) {    // functie ce afiseaza structura TMic
 
  if (argument2 < 0) {
    printf("%s/%i", cel->word, cel->count);
  } else {
    if (cel->count <= argument2)
	     printf("%s/%i", cel->word, cel->count);
  }
}

void AfiMare(TMare *cel, int argument2) { 
  // functie intermediara de afisare

  TLG u = cel->l;

  if (argument2 == -1) {
      printf("(%i:", cel->lenght);
    	for(; u != NULL; u = u->urm) {
        // printf("\n ceva \n");
        //if(u->info)
    		AfiMic(u->info, argument2);
    		if(u->urm && u->urm->info)
    			printf(", ");
    	}
     	printf(")");
  } else {
    TLG start = u;
    int flag = 0;
    for(; start != NULL; start = start->urm) {
      TMic *pMic = (TMic*)start->info;
      if (pMic->count <= argument2)
        flag = 1;
      }
      if (flag) {

        printf("(%i: ", cel->lenght);

        for(; u != NULL; u = u->urm) {

          TMic *pMic = (TMic*)u->info;
          if (pMic->count <= argument2) {

            AfiMic(u->info, argument2);

            if(u->urm && u->urm->info) {

              TMic *pMicUrm = (TMic*)u->urm->info;

              if (pMicUrm->count <= argument2)
                printf(", ");
              }
            }
              }
          printf(")");
          }
     }


	// if(!u->urm)
	// 	printf(")");
	// else
	// 	printf(") ");
}

/* functie ce intoarce 1 daca exista un element cu frecventa cuvantului */
/* mai mai mica sau egala decat valoarea argumentului primit */

int searchCount(TLG l, int argument2) {
  
  TLG q = l;
  for(;q != NULL; q = q->urm) {
    
    TMic *pCheck = (TMic*)q->info;
    if(pCheck->count <= argument2)
      return 1;
  }
  return 0;
}

/* functie ce intoarce 1 daca exista un element cu lungimea cuvantului */
/* mai mai mica sau egala decat valoarea argumentului primit */

int searchLenght(TLG l, int argument3) {
  TLG q = l;
  for(;q != NULL; q = q->urm) {
    TMare *pCheck = (TMare*)q->info;
    if(pCheck->lenght == argument3)
      return 1;
  }
  return 0;
}

/*  megafunctie de afisare */

void newAfiTH(TH* ah, int argument1, int argument2, int argument3)  //,TF AfiMare)
{
    TLG p, el;
    int flag = 0;

    if (argument1 == -1 && argument2 == -1) {

            argument1 = ah->M;
            flag = 1;

            for(int i = 0; i < argument1; i++) {
                p = ah->v[i];
                if(p) {

                    printf("pos %d: ",i);

                  for(el = p; el != NULL; el = el->urm) {
                    if(argument3 > 0) {
                      TMare *pMare = (TMare*)el->info;
                      if(pMare->lenght == argument3)
                        AfiMare(el->info, argument2);
                      else
                        continue;
                    } else
                        AfiMare(el->info, argument2);
                    }
                    printf("\n");
                  }
                }
     } else if (argument1 >= 0 && argument1 <= (int)ah->M && argument2 == -1) {

          p = ah->v[argument1];
        //  printf("%p\n", p);
          if(p) {

            for(el = p; el != NULL; el = el->urm) {

              if(argument3 > 0) {
                TMare *pMare = (TMare*)el->info;
                if(pMare->lenght == argument3)
                  AfiMare(el->info, argument2);
                else
                  continue;
              } else
                  AfiMare(el->info, argument2);
              }

              if(searchLenght(p, argument3))
                printf("\n");
    }
  } else if (argument1 == -1 && argument2 != -1) {

      argument1 = ah->M;

      for(int i = 0; i < argument1; i++) {
        p = ah->v[i];

        if(p) {
          TLG pion = p;
          int flag2 = 0;
          for(; pion != NULL; pion = pion->urm) {
            TMare *pMare = (TMare*)pion->info;
            if(searchCount(pMare->l, argument2)) {
              flag2 = 1;
            }
          }
          if(flag2) {
            printf("pos%d: ",i);
          for(el = p; el != NULL; el = el->urm) {

                AfiMare(el->info, argument2);
            }
            printf("\n");
            }
          }
        }
}

}

/*  megafunctie de inserare care face legatura dintre input, adica string */
/*  si functiile de inserare in lista */

int InserareEl(TH*a, void *ae, TFHash fh) {

  char * cuvant = (char*)ae;

  if (!a->v[fh(cuvant)]) {   // daca nu exista lista mare

    TMare *element = (TMare*)calloc(1, sizeof(TMare));
    element->lenght = (int)strlen(cuvant);
    if(!Ins_IncLG(&a->v[fh(cuvant)], (TMare*)element)) {
      return 0;
    }

    TMare * pMic = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru lista #2
    if(!Ins_IncLG(&(pMic->l), alocMic(cuvant)))
      return 0;
      
    return 1;
  } else {  //  cazul in care exista cel putin un element pentru lista asociata cuvantului in vector 

      TLG p = a->v[fh(cuvant)];

      for(; p != NULL; p = p->urm) {

        TMare *ponterMare = (TMare*)(p->info);

        if (ponterMare->lenght < (int)strlen(cuvant)) {

          if(!p->urm) {
            TMare *element = (TMare*)calloc(1, sizeof(TMare));
            element->lenght = strlen(cuvant);
            if(!Ins_IncLG(&(element->l), alocMic(cuvant)))
              return 0;
            if(!InsLG(&p, element))
              return 0;
            return 1;

            } else {

                TMare *pointer2 = (TMare*)p->urm->info;

                if(pointer2->lenght > (int)strlen(cuvant)) {
                  TMare *element = (TMare*)calloc(1, sizeof(TMare));
                  element->lenght = strlen(cuvant);
                  if(!Ins_IncLG(&(element->l), alocMic(cuvant)))
                    return 0;
                  if(!InsLG(&p, element))
                    return 0;

                  return 1;
                } else
                    continue;
            }
    }  else if (ponterMare->lenght > (int)strlen(cuvant)) {

      TMare *element = (TMare*)calloc(1, sizeof(TMare));
      element->lenght = (int)strlen(cuvant);
      if(!Ins_IncLG(&a->v[fh(cuvant)], (TMare*)element))
        return 0;

      TMare * pMare = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru al doilea tip de lista
      if(!Ins_IncLG(&(pMare->l), alocMic(cuvant))) {
        return 0;
      }
      return 1;
    } else {   // lungimi egale ale cuvintelor

      TLG u = (TLG)ponterMare->l;
      TLG ant = (TLG)ponterMare->l;
      TMic *ponterMic = (TMic*)(u->info);

      for(;u != NULL; u = u->urm) {
        ponterMic = (TMic*)(u->info);
        if(cmpAlf(ponterMic, cuvant)) {
          ponterMic->count++;
          return 1;
        }
      }

      if(!InsLG(&ant, alocMic(cuvant)))
          return 0;
       return 1;
    }
  }
  return 1;
  }
}



TMic *alocMic(char * cuvant) {
  TMic *infocuv = (TMic*)calloc(1, sizeof(TMic));
  infocuv->word = (char*)calloc(1, strlen(cuvant)+1);
  infocuv->count = 1;
  strcpy(infocuv->word, cuvant);   // alocare info pentru lista #2
  return infocuv;
}

int cmpAlf(void * e1, void * e2) {  // comparatie alfanumerica intre doua stringuri
	TMic * info1 = (TMic *) e1;
	char * info2 = (char *) e2;
	if (strcmp(info1->word, info2) == 0)
		return 1;
	return 0;
}

/*functie auxiliara de sortare*/

void sortAux(TH *h) {  
//  printf("a\n");
    for(int i = 0; i < (int)h->M; i++) {
  //    printf("%d\n", i);
      TLG pPrincipal = h->v[i];
      if(pPrincipal) {
      //  printf("1cv\n");
        for(;pPrincipal != NULL; pPrincipal = pPrincipal->urm) {
          TMare *pInfoMare = (TMare*) pPrincipal->info;
          TLG u = (TLG) pInfoMare->l;
    //      printf("2cv\n");
          bobelsort(&u);
        }
      }
    }
    return;
}

/*functie de swap care schimba valorile elementelor*/

void swap(TLG a, TLG b) {

    TMic *temp = (TMic*)calloc(1, sizeof(TMic));
    TMic *infoa = (TMic*)a->info;
    TMic *infob = (TMic*)b->info;
    int max = infob->count - infoa->count > 0 ? infob->count : infoa->count;

    temp->count = infoa->count;

    temp->word = (char*)calloc(1, max);
    strcpy(temp->word, infoa->word);

    infoa->count = infob->count;
    strcpy(infoa->word, infob->word);

    infob->count = temp->count;
    strcpy(infob->word, temp->word);
}


/*functie de sortare a elementelor din al doilea tip de lista utilizand bubblesort*/

void bobelsort(TLG *l) {
  TLG p , ant = NULL;
  int conditie = 1;


while (conditie) {
      p = *l;
    conditie = 0;
    while (p->urm != NULL) {
          TMic *infoActual = (TMic*)p->info;
    //      printf("|111%s|\n", infoActual->word);
          TMic *infoUrm = (TMic*)p->urm->info;
    //      printf("|222%s|\n", infoUrm->word);
        if (infoActual->count < infoUrm->count) {
            swap(p, p->urm);
            conditie = 1;

        } else if (infoActual->count == infoUrm->count) {
          if (strcmp(infoActual->word,infoUrm->word) > 0) {
            swap(p, p->urm);
            conditie = 1;
          }
        }
        p = p->urm;
    }
    ant = p;
  }
}


/*  functie de eliberare a unei celule de tip TMic*/

void eliberareTMic(TMic *el) {
//  printf("da sefule\n");
free(el->word);
free(el);
}

/*  functie de eliberare a unei celule de tip TMare*/

void eliberareTMare(void *elem, TF eliberarTMic) {

  TMare *el = (TMare*)elem;
  TLG u = el->l;
  TLG aux;

  for(;u != NULL; u = u->urm) {
    aux = u;
    TMic *bwoah = (TMic*) aux->info;
    eliberareTMic(aux->info);
  }
  
}

int main(int argc, char *argv[]) {

  TH *h = NULL;
  h = InitTH('Z' - 'A' + 1 , codHash);
  FILE *input;
  input = fopen(argv[1], "r");

  while(argc) {
    // start citire & prelucrare comanda
    char *comanda = (char*)calloc(lineSize, sizeof(char));
    char **cuvant = (char**)calloc(wordSize, sizeof(char*));
    int contor1 = 0;
    if(!fgets(comanda, lineSize, input)) {
      break;
    }
    if(strrchr(comanda, '\n')) {
      *strrchr(comanda, '\n') = '\0';
    }
    cuvant[contor1] = strtok(comanda, " .,");

    while (cuvant[contor1]) {    // while de parsare

      if(contor1 == 0 && strcmp(cuvant[0], "print")) {
        contor1++;
        cuvant[contor1]=strtok(NULL, " .,");
        continue;
      }
      // end citire & prelucrare comanda
      // start insert block

      if (strcmp(cuvant[0], "insert") == 0) {
          if(strlen(cuvant[contor1]) < 3 ||(*cuvant[contor1] < '9' && *cuvant[contor1] > '0')) {
            contor1++;
            cuvant[contor1]=strtok(NULL, " .,");
            continue;
          }
          if(!InserareEl(h, cuvant[contor1], codHash)) {
            printf("Inserare nereușita\n");
            return 1;
          }
      }

      // end insert block
      // start print block

      if (strcmp(cuvant[0], "print") == 0) {

        while (cuvant[contor1]) {
          contor1++;
          cuvant[contor1]=strtok(NULL, " .,");
        }

        int argument1 = -1;
        int argument2 = -1;
        int argument3 = -1;
         sortAux(h);
         if(contor1 == 2) {
           if(*cuvant[1] - 'a' <= 26 && *cuvant[1] - 'a' >= 0) {
             argument1 = (int)(*cuvant[1] - 'a');
            } else if (*cuvant[1] - 'A' <= 26 && *cuvant[1] - 'A' >= 0) {
            argument1 = (int)(*cuvant[1] - 'A');
            } else if (*cuvant[1] - '0' <= 9 && *cuvant[1] - '0' >= 0) {
            argument2 = atoi(cuvant[1]);
            } else
                return 1;
        } else if (contor1 == 3) {

          if (*cuvant[1] - 'a' <= 26 && *cuvant[1] - 'a' >= 0)
            argument1 = (int)(*cuvant[1] - 'a');
          else if (*cuvant[1] - 'A' <= 26 && *cuvant[1] - 'A' >= 0)
            argument1 = (int)(*cuvant[1] - 'A');
          argument3 = atoi(cuvant[2]);
         }

        newAfiTH(h, argument1, argument2, argument3);
        continue;
      }
      contor1++;
      cuvant[contor1]=strtok(NULL, " .,");

    }
    free(comanda);

  }
  DistrTH(&h, (TF)eliberareTMare);
  fclose(input);
  return 0;
}
