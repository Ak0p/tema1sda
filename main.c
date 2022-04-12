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

void AfiMic(TMic *cel, int argument2) {
 // printf("        afimic %d          ", argument2);
  if (argument2 < 0) {
    printf("%s/%i", cel->word, cel->count);
  }
  else {
    if (cel->count <= argument2)
	     printf("%s/%i", cel->word, cel->count);
  }
}
void AfiMare(TMare *cel, int argument2) {
  // printf("nununu\n");
  	TLG u = cel->l;
  // printf("n-am idee\n");
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

int searchCount(TLG l, int argument2) {
  TLG q = l;
  for(;q != NULL; q = q->urm) {
    TMic *pCheck = (TMic*)q->info;
  //  printf("\n%d\n", pCheck->count);
    if(pCheck->count <= argument2)
      return 1;
  }
  return 0;
}

int searchLenght(TLG l, int argument3) {
  TLG q = l;
  for(;q != NULL; q = q->urm) {
    TMare *pCheck = (TMare*)q->info;
  //  printf("\n%d\n", pCheck->count);
    if(pCheck->lenght == argument3)
      return 1;
  }
  return 0;
}

void newAfiTH(TH* ah, int argument1, int argument2, int argument3)  //,TF AfiMare)
{
    TLG p, el;
    int flag = 0;
    if (argument1 == -1 && argument2 == -1) {
            argument1 = ah->M;
            flag = 1;

            for(int i = 0; i < argument1; i++) {
                p = ah->v[i];
              //  printf("%p\n", p);
                if(p) {
                  //  printf("dadada\n");
                    printf("pos %d: ",i);
                  for(el = p; el != NULL; el = el->urm) {
                //    //      printf("dadada\n");
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
                  // if(!flag)
                  //   break;
                }
     } else if (argument1 >= 0 && argument1 <= (int)ah->M && argument2 == -1) {


          p = ah->v[argument1];
        //  printf("%p\n", p);
          if(p) {
            //  printf("dadada\n");


            for(el = p; el != NULL; el = el->urm) {
          //      printf("dadada\n");
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
      flag = 1;
    for(int i = 0; i < argument1; i++) {
        p = ah->v[i];
        flag = 1;
      //  printf("%p\n", p);
        if(p) {
          TLG pion = p;
          int flag2 = 0;
          for(; pion != NULL; pion = pion->urm) {
            TMare *pMare = (TMare*)pion->info;
            if(searchCount(pMare->l, argument2)) {
              flag2 = 1;
            }
          }
    //      printf("Eu %d\n", flag2);
          if(flag2) {
            printf("pos%d: ",i);
          for(el = p; el != NULL; el = el->urm) {

                AfiMare(el->info, argument2);
            }
            printf("\n");
            }
          }
          // if(!flag)
          //   break;
        }
}

}

int InserareEl(TH*a, void *ae, TFHash fh) {
  char * cuvant = (char*)ae;
  //    printf("\n|%s|\n", cuvant);

  if (!a->v[fh(cuvant)]) { // daca nu exista lista mare
    TMare *element = (TMare*)calloc(1, sizeof(TMare));
    element->lenght = (int)strlen(cuvant);
    //printf("\n\n\nTESTARE1 ||||| %p ||||||\n", element->l->urm);   // alocare info lista #!
    if(!Ins_IncLG(&a->v[fh(cuvant)], (TMare*)element)) {
      return 0;
    }
//    printf("nue lma: %s\n", cuvant);

    TMare * pointerUseless = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru lista #2
    if(!Ins_IncLG(&(pointerUseless->l), alocMic(cuvant))) {

      return 0;
    }
  //  printf("TESTARE1 ||||| %p  %p ||||||\n\n\n", element->l->urm, element->l->urm->urm);
  //  printf("Ori aci\n");
    // pointerUseless = NULL;
    return 1;
  } else {
//    printf("exista lma: %s\n", cuvant);
      TLG p = a->v[fh(cuvant)];
    //  int ji = 0;
      for(; p != NULL; p = p->urm) {
        // printf("\nji - %d\n", ji);
      //  ji++;
        TMare *ponterMare = (TMare*)(p->info);
      //  printf("\n cv \n");
        if (ponterMare->lenght < (int)strlen(cuvant)) {
  //        printf("mai mare\n");
          if(!p->urm) {
            TMare *element = (TMare*)calloc(1, sizeof(TMare));
            element->lenght = strlen(cuvant);
            if(!Ins_IncLG(&(element->l), alocMic(cuvant)))
              return 0;
            if(!InsLG(&p, element))
              return 0;
            return 1;


          //    continue;
            } else {

                TMare *pointer2 = (TMare*)p->urm->info;
                // ponterMare = (TMare*)p->urm->info;
                if(pointer2->lenght > (int)strlen(cuvant)) {
  //               printf("mai mic/e: %s\n", cuvant);
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
      if(!Ins_IncLG(&a->v[fh(cuvant)], (TMare*)element)) {
        return 0;
      }
      // a->v[fh(cuvant)]->urm = NULL;
  //    printf("nue lma: %s\n", cuvant);
      TMare * pointerUseless = (TMare*) a->v[fh(cuvant)]->info;   // alocare info pentru lista #2
      if(!Ins_IncLG(&(pointerUseless->l), alocMic(cuvant))) {
        //printf("Aci\n");
        free(pointerUseless);
        return 0;
      }
      return 1;
    } else {


//      printf("egal: %s\n", cuvant);
  //    printf("egal?\n");
      TLG u = (TLG)ponterMare->l;
      TLG ant = (TLG)ponterMare->l;
      TMic *ponterMic = (TMic*)(u->info);
//      printf("ant-initial: %p u-initial: %p %s\n",ant, u, ponterMic->word);
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
//      printf("ant-final: %p u-final: %p\n",ant, u);
//     printf("egal/nu  e: %s\n", cuvant);
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

int cmpAlf(void * e1, void * e2) {
	TMic * info1 = (TMic *) e1;
	char * info2 = (char *) e2;
	if (strcmp(info1->word, info2) == 0)
		return 1;
	return 0;
}

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
      fclose(input);
      return 0;
    }
    if(strrchr(comanda, '\n')) {
      *strrchr(comanda, '\n') = '\0';
    }
    cuvant[contor1] = strtok(comanda, " .,");

    while (cuvant[contor1]) {
//      printf("%d - %s\n", contor1, cuvant[contor1]);
      if(contor1 == 0 && strcmp(cuvant[0], "print")) {
        contor1++;
        cuvant[contor1]=strtok(NULL, " .,");
        continue;
      }
      // contor1++;
      // end citire & prelucrare comanda
      // start insert block
      if (strcmp(cuvant[0], "insert") == 0) {
          if(strlen(cuvant[contor1]) < 3 ||(*cuvant[contor1] < '9' && *cuvant[contor1] > '0')) {
            contor1++;
            cuvant[contor1]=strtok(NULL, " .,");
            continue;
          }

          // printf("|%d\n", contor1);
          if(!InserareEl(h, cuvant[contor1], codHash)) {
            printf("Inserare nereușita\n");
            return -1;
          }
      }

      // end insert block
      // start print block

      if (strcmp(cuvant[0], "print") == 0) {

        while (cuvant[contor1]) {
          contor1++;
          cuvant[contor1]=strtok(NULL, " .,");
        }

        // int argument1 = h->M;
        // u_int argument2 = ~0;
        int argument1 = -1;
        int argument2 = -1;
        int argument3 = -1;
         sortAux(h);
         if(contor1 == 2) {
           if(*cuvant[1] - 'a' <= 26 && *cuvant[1] - 'a' >= 0) {
             argument1 = (int)(*cuvant[1] - 'a');
        //     printf("a2, arg1 : %d\n", argument1);
            }
          else if (*cuvant[1] - 'A' <= 26 && *cuvant[1] - 'A' >= 0) {
            argument1 = (int)(*cuvant[1] - 'A');
      //      printf("A2, arg1 : %d\n", argument1);
            }
          else if (*cuvant[1] - '0' <= 9 && *cuvant[1] - '0' >= 0) {
            argument2 = atoi(cuvant[1]);
        //    printf("A2, arg2 : %d\n", argument2);
            }
          else
            return 1;
        } else if (contor1 == 3) {
          if (*cuvant[1] - 'a' <= 26 && *cuvant[1] - 'a' >= 0)
            argument1 = (int)(*cuvant[1] - 'a');
          else if (*cuvant[1] - 'A' <= 26 && *cuvant[1] - 'A' >= 0)
            argument1 = (int)(*cuvant[1] - 'A');
          argument3 = atoi(cuvant[2]);
      //    printf("|%d %d|\n", argument1, argument3);
         }
      //  printf("\napel %d %d %d\n", argument1, argument2, argument3);
        newAfiTH(h, argument1, argument2, argument3);
        contor1++;
        cuvant[contor1]=strtok(NULL, " .,");
        continue;
      }
      contor1++;
      cuvant[contor1]=strtok(NULL, " .,");
    }
    free(comanda);
    // for(int i = 0; i < contor1; i++)
    //   free(cuvant[i]);
  }
//c  DistrTH(&h, );
  fclose(input);
  return 0;
}
