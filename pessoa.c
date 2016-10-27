/**
 *  @file pessoa.c
 *  @brief Implementation of some function prototypes for project of aed1.
 *
 *  This file contains the implementations for
 *  some functions to process structs pessoa that will be needed for the aed1 project.
 *
 *  @author José Torres (jtorres@ufp.edu.pt)
 *  @bug No known bugs.
 */

#include "pessoa.h"
#include "string_sorting.h"
#include <string.h>
#include "lib_util.h"
#include "quickunion.h"
#define MAX_M 25
#include <stdio.h>
#include <stdlib.h>



extern pessoa * personsDB;
extern int personDBSize;


/** Imprime o Conteudo dentro da base de dados */

void lerbasedados(pessoa * personsDB,int personDBSize)
{
    system("cls");
    int i=0;
    printf("\nConteudo da base de dados:\n");
    for (i=0; i<personDBSize; i++)
    {
        printPerson(&personsDB[i]);
    }

    char c;

    printf(" Pression \"f\" para voltar ao menu!\n");
    getchar();
    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }

}


/** Adiciona uma nova pessoa à BD e faz o resize da mesma */

void adicionapessoa()
{
    pessoa nova;
    printf("Insira nif 9 chars:\n");
    getchar();
    gets(nova.nif);

    printf("Insira nome :\n");

    gets(nova.nome);


    printf("Insira morada:\n");

    gets(nova.morada);


    printf("Insira datanascimento :\n");

    gets(nova.datanascimento);


    printf("Insira cod postal:\n");

    gets(nova.cod_postal);


    printf("Insira freguesia:\n");

    gets(nova.freguesia);


    printf("\nInsercao feita com sucesso!\n");
    createnewperson(nova.nif,nova.nome,nova.datanascimento,nova.morada,nova.cod_postal,nova.freguesia);

    char c;

    printf(" Pressione \"f\" para voltar ao menu!\n");

    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }
}


/** Cria automaticamente 1000 structs pessoa com dados aleatórios e insere-os na nossa bd!
*
*
*
*
*/

void cria1000(){

    int i=0;
    char nif[10];
    char nome[MAX_M];
    char data[9];
    char morada[MAX_M];
    char cod_postal[8];
    char  freguesia[MAX_M];

    for (i=0;i<1000;i++){
            preencherandom(&nif,&nome,&data,&morada,&cod_postal,&freguesia);
            createnewperson(nif,nome,data,morada,cod_postal,freguesia);
    }


            printf(" Sucesso!, 1 novas pessoas foram adicionadas à sua BD! \n");

        lerbasedados(personsDB,personDBSize);
        menu(personsDB,personDBSize);


}


/** Cria uma pessoa com dados aleatórios
*   @param cbar* nif
* @param char* nome
*@param char* data
*@param char* morada
* @param char* cod_postal
* @param char * freguesia
*
*/

void preencherandom(char* nif, char* nome, char* data, char* morada,char* cod_postal,char*  freguesia){
    char auxnome[]="ABCDEFGHIJKLMNOPQRSTUVXYZ";
    char auxnum[]="1234567890";
    int i=0,j,c,t,k;
    int x;


    for(i=0;i<9;i++){
            x=rand()%10;
            *(nif+i)=auxnum[x];
            }
        *(nif+i)='\0';

 for(k=0;k<MAX_M-1;k++){
            x=rand()%23;
            *(nome+k)=auxnome[x];
            }
        *(nome+(k))='\0';

        for(j=0;j<8;j++){
            x=rand()%10;
            *(data+j)=auxnum[x];
            }
        *(data+j)='\0';


         for(t=0;t<MAX_M-1;t++){
            x=rand()%23;
            *(morada+i)=auxnome[x];
            }
        *(nome+(i))='\0';

         for(c=0;c<MAX_M-1;c++){
            x=rand()%23;
            *(cod_postal+i)=auxnome[x];
            }
        *(nome+(i))='\0';

         for(i=0;i<MAX_M-1;i++){
            x=rand()%23;
            *(freguesia+i)=auxnome[x];
            }
        *(nome+(i))='\0';

        printf(" %s \n %s \n %s \n %s \n",nif,nome,data,freguesia);

}



void clientReadFilePerson()
{
    pessoa * pessoasArray = NULL;
    int i, n = 0;
    // should use relative path instead: "../data/3persons.txt"
    pessoasArray = readFilePerson("C:/projetos/projetoaed1/data/3persons.txt", &n);
    for (i=0; i<n; i++)
    {
        printPerson(&pessoasArray[i]);
    }

    readFilePersonFamily("C:/projetos/projetoaed1/data/3persons-family.txt");
}

/** Lê ficheiro txt com 4 argumentos: 1º nif da pessoa que vai ser explorada, 2º numero de elementos a unir, 3º e 4º 2 nifs correspondendo às pessoas que pertencem
ao primeiro associado */
int lerunionfile(pessoa * personsDB,int personDBSize)
{
    system("cls");
    FILE *fPointer;
    //char singleLine[150];

    char** ppaux=NULL;
    ppaux=(char**)malloc(sizeof(char*)*10);
    int i=0;

    fPointer =fopen("C:/projetos/projetoaed1/data/familia.txt","r");
    if (!fPointer)
        return 1;

    while (!feof(fPointer))
    {
        *(ppaux+i)=(char*)malloc(sizeof(char)*50);
        fgets(*(ppaux+i), 150, fPointer);
        puts(*(ppaux+i));
        // printf("%s",*(ppaux+i));
        i++;
    }

//            for(i=0;i<3;i++){
//                printf("\n%s\n",*(ppaux+i));
//                }
    int numero= atoi(*(ppaux+0));
    //printf(" %d sss\n",numero);



    fazerUnion(personsDB,personDBSize,ppaux,numero+1);


    fclose(fPointer);
    return 0;


}



/** Recebe a BD, o tamanho da bd, o array de strings aux e o size desta mesma. Vai buscar os indices correspondentes de cada nif
e usa-os para fazer a união das pessoas e no fim poder imprimir os respectivos nomes das pessoas em familia */
void fazerUnion(pessoa * personsDB,int personDBSize,char** ppaux,int numero)
{

    int i=0,j=0;
    char** astrs=NULL;
    astrs=(char**)malloc(sizeof(char*)*10);
    const char s[2] = ";";


    /* get the first token */
    *(astrs+0)=(char*)malloc(sizeof(char)*10);
    *(astrs+0)= strtok(*(ppaux+1),s);
//   printf( "%s\n", *(astrs+0) );

    /* walk through other tokens */

    while( *(astrs+i) != NULL )
    {
        i++;
        *(astrs+i)=(char*)malloc(sizeof(char)*11);
        *(astrs+i)=strtok(NULL, s);
//       printf( "%s\n", *(astrs+i) );

    }
//   printf( " %s\n", *(astrs+2) );

    int size=atoi(*(astrs+1))+1;
    int unionQ[personDBSize];

    for(i=0; i<0; i++)
    {
        unionQ[i]=i;
    }



    initQU(unionQ,personDBSize);


    printf(" %s---  \n",*(astrs+0));
    printf(" %s---  \n",*(astrs+1));
    printf(" %s--- \n",*(astrs+2));
    printf(" %s---  \n",*(astrs+3));
     i=0;
     j=0;
    int primeiro=0,outro=0;
    primeiro=indice(0,personsDB,personDBSize,astrs,size);
    int    segundo=indice(2,personsDB,personDBSize,astrs,size);
    int  terceiro=indice(3,personsDB,personDBSize,astrs,size);
    //          for(i=0;i<3;i++){
//       printf(" %d \n",unionQ[i]);
//       }
    unionQU(unionQ,size,segundo,primeiro);
    unionQU(unionQ,size,terceiro,primeiro);

    for(i=0;i<personDBSize;i++){
        printf(" %d ",unionQ[i]);
    }



    for(i=0; i<personDBSize; i++)
    {
        if(i==primeiro){
            printf(" Pessoas da familia de %s : \n",personsDB[i].nome);

            for(j=0;j<personDBSize;j++){
                    if(unionQ[j]==primeiro && j!= primeiro){
                        printf(" -> %s \n",personsDB[j].nome);
                    }


            }
        }
    }
}

/**
 * Indice - retorna o valor do indice na BD daquela string que se pretende procurar, neste caso a funçao é usada no union quando se quer saber o indice
 *`daquela string na matriz aux.
 *
 *
 *  @param pessoa* personsDB a nossa BD
 *  @param int personDBSize tamanho BD
 * @param char** astrs a nossa matriz com os nifs a procurar
 *  @param int siz tamanho da matriz aux
 * @param int value valor do indice na matriz
 */
int indice(int value,pessoa *personsDB,int personDBSize,char** astrs,int siz){
    int j=0;
//    printf(" %s \n",personsDB[0].nome);
//    printf(" %s \n",personsDB[7].nome);
//    printf(" %s \n",personsDB[2].nome);
            while(j<personDBSize){
                if(strcmp(*(astrs+value),personsDB[j].nif)==0){
                        printf(" %d INDICEEE \n",j);
                    return j;
                }
                j++;
            }
return -1;

}




/**
   Simple test client 2 for the functions to manipulate pessoas
   Updates the database of persons (global variable personsDB)
 */
void clientReadFilePerson2()
{
    pessoa  * pessoasArray = NULL;
    int n=0;


    // should use relative path instead: "../data/3persons.txt"
    pessoasArray = readFilePerson("C:/projetos/projetoaed1/data/3persons.txt", &n);


    if (personDBSize == 0)
    {
        personsDB = pessoasArray;
        personDBSize = n;
    }
    else
    {
        personsDB = concatPersonArrays(personsDB, personDBSize, pessoasArray, n, 1);
        personDBSize = personDBSize + n;
    }

    pessoasArray = readFilePerson("C:/projetos/projetoaed1/data/4persons.txt", &n);
    if (personDBSize == 0)
    {
        personsDB = pessoasArray;
        personDBSize = n;
    }
    else
    {
        personsDB = concatPersonArrays(personsDB, personDBSize, pessoasArray, n, 1);
        personDBSize = personDBSize + n;
    }

    menu(personsDB,personDBSize);
}

//    // add a new person
//    pessoa p = {"333333351","Ana Silva","20150101","Avenida dos Aliados Norte, 352","4249020","Paranhos"};
//    personsDB = addPerson2PersonArray(personsDB, personDBSize, &p);
//    personDBSize = personDBSize + 1;


/**
 * MENU
 *
 *
 *  @param pessoa* pessoas a nossa BD
 *  @param int personDBSize tamanho BD
 */
void menu(pessoa * personsDB, int personDBSize)
{
    system("cls");
    int choice;
    char strnome[10];

    printf("PROJETO AED1-Menu-BD\n\n");
    printf("1. Imprimir Basedados;\n");
    printf("2. ExportarBD\n");
    printf("3. ORNEDAR BD MSD\n");
    printf("4. ORNEDAR BD LSD\n");
    printf("5. RemoverPessoa\n");
    printf("6. INSERIRPessoa\n");
    printf("7. QuickUnion\n");
    printf("8. Atualizar\n");
    printf("9. PesquisaBinária\n");
    printf("10. Custostemporaisfuns\n");
    printf("11. Cria 1000 Pessoas Random\n");
    printf("12. Exit\n");
    scanf("%d",&choice);
    char str[15];
    StringElementsArray a;
    int count=0;

    switch (choice)
    {
    case 1:
        lerbasedados(personsDB,personDBSize);
        break;
    case  2:
        printf("\n Nome do ficheiro txt?:\n");
        getchar();
        gets(strnome);
        writeDB(personsDB,personDBSize,strnome);
        break;
    case 3:
        MSD_sort(personsDB,personDBSize);
        break;
    case 4:
        LSD_sort(personsDB,personDBSize);
        break;
    case 5:
        printf("Nome da pessoa a remover?\n");
        getchar();
        gets(str);
        personsDB=removePessoa(personsDB,&personDBSize,str);
        menu(personsDB,personDBSize);
        break;
    case 6:
        adicionapessoa();
        break;
    case 7:
        choice=lerunionfile(personsDB,personDBSize);
        break;
    case 8:
        atualizarpessoa();
        break;
    case 9:
        a=MSD_sort_NOME(personsDB,personDBSize);
        system("cls");
        printf("Quem deseja pesquisar?:\n");
        gets(str);
        printf(" %s \n",str);
        count=binarysearch(a,str,0,personDBSize);
        if(count==-1)
        {
            printf("Nao existe!\n");
        }
        else
        {
            printf("Existe!");
        }
        break;
    case 10:
        custos(personsDB,personDBSize);
        break;
        case 11:
        cria1000();
        break;
    case 12:

        printf("GOODBYE!\n");
        break;


    default:
        printf("Wrong Choice. Enter again\n");
        break;
    }


    //personsDB=removePessoa(personsDB,&personDBSize,"Pedro Galocha");
//    printf(" \n Nova DB! \n");
//    for (i=0; i<personDBSize; i++)
//    {
//        printPerson(&personsDB[i]);
//    }

//    printf("\n %d---- \n",personDBSize);
//
//    printf(" \n %s \n",personsDB[1].nif);
//    printf(" \n %s \n",personsDB[0].nif);
//    personsDB[1]=personsDB[0];
//    pessoa * aux;
//    aux=&personsDB[0];
//    printf("\n %s \n",(*aux).nome);
//    printf("\n %s \n",(*aux).nif);
//    printf(" \n %s \n",personsDB[1].nif);
//    printf(" \n %s \n",personsDB[1].nome);


    // LSD_sort_data(personsDB,personDBSize);


}

 /**
 * Custos
 *
 *
 *  @param pessoa* pessoas a nossa BD
 *  @param int personDBSize tamanho BD
 */



void custos(pessoa* personsDB,int personDBSize)
{
    char name;
    int  number;
    FILE *f;
    f = fopen("custos.txt", "w");

    StringElementsArray a;

    long long tinit;
    long long tend;
    long elapsed_time;
    int value=0;
    char str[15];
    int count=0;
//    printf("PROJETO AED1-Menu-BD-Custos\n\n");
// printf("1. MSD;\n");
// printf("2. LSD\n");
// printf("3. BinarySearch\n");
// printf("4. Union\n");
// scanf("%d",&value);


// switch(value){
// case 1:
    gettimeuseconds(&tinit); // Tempo Inicial
    MSD_sort(personsDB,personDBSize);
    gettimeuseconds(&tend); // Tempo Final
    elapsed_time = (long)(tend - tinit);
    //printf("Execucao MSD %ld:\n",elapsed_time);
    fprintf(f, "MSD: %ld ms\n",elapsed_time);
//    break;
// case 2:
    gettimeuseconds(&tinit); // Tempo Inicial
    LSD_sort(personsDB,personDBSize);
    gettimeuseconds(&tend); // Tempo Final
    elapsed_time = (long)(tend - tinit);
   // printf("Execucao LSD %ld:\n",elapsed_time);
    fprintf(f, "LSD: %ld us\n",elapsed_time);
//    break;
// case 3:
    gettimeuseconds(&tinit); // Tempo Inicial
    a=MSD_sort_NOME(personsDB,personDBSize);
    system("cls");
    printf("Quem deseja pesquisar?:\n");
    gets(str);
    //printf(" %s \n",str);
    count=binarysearch(a,str,0,personDBSize);

    gettimeuseconds(&tend); // Tempo Final
    elapsed_time = (long)(tend - tinit);
   // printf("Execucao Binary %ld:\n",elapsed_time);
    fprintf(f, "Binary: %ld us\n",elapsed_time);
//    break;
// case 4:
    gettimeuseconds(&tinit); // Tempo Inicial
    lerunionfile(personsDB,personDBSize);
    gettimeuseconds(&tend); // Tempo Final
    elapsed_time = (long)(tend - tinit);
   // printf("Execucao UNION %ld:\n",elapsed_time);
    fprintf(f, "UNION: %ld us\n",elapsed_time);
    fclose(f);


}

 /**
 * binarysearch
 *
 *
 *  @param StringElementsArray pessoas o nosso array ordenado a ser pesquisado
 *  @param int lo indice mais baixo
 *   @param int hi indice mais alto
 *   @param char * str nome da pessoa a pesquisar
 *   @return int mid retorna o indice se encontrar da pessoa
 *
 */

int binarysearch(StringElementsArray pessoas,char*str,int lo,int hi)
{
    int value=0;
    int mid=0;
    while (lo <= hi)
    {
        mid =(lo + hi)/2;
        value=strcmp(pessoas.str[mid],str);
        if(value==0)
        {
            printf("Existe !!!");
            return mid;
        }

        else if (value==-1)
        {
            lo=mid+1;
        }
        else if(value==1)
        {
            hi=mid-1;
        }
    }
    return -1;
    printf("Nao existe!");
    // não encontrado
}


 /**
 * Actualiza a informacao de uma pessoa, faz a sua busca pelo nome
 *
 *
 *
 *
 */
void atualizarpessoa()
{
    int i=0;
    char nome[15];
    printf("Insira o nome da pessoa na bd a editar:\n");
    getchar();
    gets(nome);
    for(i=0; i<personDBSize; i++)
    {
        if(strcmp(personsDB[i].nome,nome)==0)
        {
            printf("\n Novo nome:\n");
            gets(personsDB[i].nome);

        }


    }

    char c;

    printf(" Pression \"f\" para voltar ao menu!\n");

    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }
}

 /**
 * Cliente MSD nome
 *
 *
 *  @param pessoa*  pessoas a nossa bd
 *  @param int n tamanho do nosso Array
 *
 *
 *    @return StringElementsArray a
 *
 */

StringElementsArray MSD_sort_NOME(pessoa* pessoas,int n)
{
    system("cls");

    int i,N=n;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArray(&a,N);
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].nome;
        a.len[i] = strlen(pessoas[i].nome);
    }
    createStringElementsArray(&aux,N);

    printf("Estado Inicial (sem MSD):\n");
    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    MSD(&a,&aux,0,N-1,0,TAMANHO_ASCII);





    printf("\n-------------\nEstado Final (com MSD):\n");
    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);
    }

    exportaMSD(&a,personDBSize);


    return a;

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);
}
 /**
 * Cliente MSD ordena por freguesia
 *
 *
 *  @param pessoa*  pessoas a nossa bd
 *  @param int n tamanho do nosso Array
 *
 *
 *
 *
 */

void MSD_sort_FREGUESIA(pessoa* pessoas,int n)
{
    system("cls");

    int i,N=n;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArray(&a,N);
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].freguesia;
        a.len[i] = strlen(pessoas[i].freguesia);
    }
    createStringElementsArray(&aux,N);

    printf("Estado Inicial (sem MSD):\n");
    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    MSD(&a,&aux,0,N-1,0,TAMANHO_ASCII);


    printf("\n-------------\nEstado Final (com MSD):\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    char c;
    printf(" Pression \"f\" para voltar ao menu!\n");
    getchar();
    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }

}


 /**
 * Cliente MSD ordena por data
 *
 *
 *  @param pessoa*  pessoas a nossa bd
 *  @param int n tamanho do nosso Array
 *
 *
 *
 *
 */

void MSD_sort_DATA(pessoa* pessoas,int n)
{
    system("cls");

    int i,N=n;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArray(&a,N);
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].datanascimento;
        a.len[i] = strlen(pessoas[i].datanascimento);
    }
    createStringElementsArray(&aux,N);

    printf("Estado Inicial (sem MSD):\n");
    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    MSD(&a,&aux,0,N-1,0,TAMANHO_ASCII);


    printf("\n-------------\nEstado Final (com MSD):\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    char c;
    printf(" Pression \"f\" para voltar ao menu!\n");
    getchar();
    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }

}

 /**
 * Cliente MSD
 *
 *
 *  @param pessoa*  pessoas a nossa bd
 *  @param int n tamanho do nosso Array
 *
 *
 *
 *
 */
void MSD_sort(pessoa * pessoas, int n)
{
    system("cls");
    int choice;


    printf("PROJETO AED1-Menu-BD-MSD\n\n");
    printf("1. ORDENAR NOME \n");
    printf("2. ORDENAR DATA \n");
    printf("3. ORDENAR FREGUESIA\n");
    printf("5. EXIT\n");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        MSD_sort_NOME(personsDB,personDBSize);
        break;
    case 2:
        MSD_sort_DATA(personsDB,personDBSize);
        break;
    case 3:
        MSD_sort_FREGUESIA(personsDB,personDBSize);
    }


}
 /**
 * Cliente LSD
 *
 *
 *  @param pessoa*  pessoas a nossa bd
 *  @param int n tamanho do nosso Array
 *
 *
 *
 *
 */
void LSD_sort(pessoa * pessoas, int n)
{
    system("cls");
    int i,W=9,R=TAMANHO_ASCII;

    StringElementsArray a;
    createStringElementsArray(&a,n);

    for (i = 0; i < n; i++)
    {
        a.str[i]=pessoas[i].nif; //Copia o nif para o atributo str da struct StringElementsArray
        a.len[i] = strlen(pessoas[i].nif); // Tamanho de cada string nif
    }



    printf("Estado Inicial (sem LSD):\n");

    for (i = 0; i < n; i++)
        printf("\t%s\n",a.str[i]);


    lsd_sort(&a,n,W,R);//chamar funçao lsd_sort, que e o algoritmo que faz o sorting

    printf("\n-----------------\nEstado Final (com LSD):\n");
    for (i = 0; i < n; i++)
        printf("\t%s\n",a.str[i]);

    char c;

    printf(" Pression \"f\" para voltar ao menu!\n");
    getchar();
    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }

}


 /**
 * Ordenaçao LSD da BD pelas datas
 *
 *
 *  @param pessoa*  pessoas a nossa struct
 *  @param int  n tamanho do nosso struct
 *
 *
 *
 *
 */

void LSD_sort_data(pessoa * pessoas, int n)
{
    int i,W=9,R=TAMANHO_ASCII;

    StringElementsArray a;
    createStringElementsArray(&a,n);

    for (i = 0; i < n; i++)
    {
        a.str[i] = pessoas[i].datanascimento; //Copia a data para o atributo str da struct StringElementsArray
        a.len[i] = strlen(pessoas[i].datanascimento); // Tamanho de cada string data
    }
    printf("Estado Inicial (sem LSD):\n");

    for (i = 0; i < n; i++)
        printf("\t%s\n",a.str[i]);

    lsd_sort(&a, n, W, R); //chamar funçao lsd_sort, que e o algoritmo que faz o sorting

    printf("\n-----------------\nEstado Final (com LSD):\n");
    for (i = 0; i < n; i++)
        printf("\t%s\n",a.str[i]);

}


 /**
 * Remove uma pessoa da bd caso ela exista!
 *
 *
 *  @param StringElementsArray*  aux o nosso array de elementos
 *  @param int * pSize tamanho do nosso Array
 *  @param char teste[] string que queremos pesquisar para remoçao
 *
 *  @return pessoa * NEWpersonsDB
 *
 */
// Função que procura o nome da pessoa e a remove da nossa base de dados

pessoa* removePessoa(pessoa * personsDB,int *pSize,char teste[])
{
    int i=0,j=0,resultado;

    int NEWpersonDBSize;
    NEWpersonDBSize=(*pSize)-1;

    pessoa * NEWpersonsDB=NULL;

    NEWpersonsDB=malloc(NEWpersonDBSize * sizeof(pessoa));

    //printf(" %s ..\n",NEWpersonsDB[0].nome);
//
//
//    printf("---------------------------------- %s \n",personsDB[0].nome);
//
//    resultado=strcmp(personsDB[0].nome,teste);
//    printf("---------------------------------- %d \n",resultado);
//    printf(" %s  %s \n",personsDB[0].nome,personsDB[2].nome);
//    strcpy(NEWpersonsDB[0].nome,personsDB[3].nome);
//    printf("-----------------------AQUI----------- %s \n",NEWpersonsDB[0].nome);


    for(i=0; i<(*pSize); i++)
    {
        resultado=strcmp(personsDB[i].nome,teste);
        //printf(" %d  %d \n",i,resultado);
        if(resultado==0)
        {
            i++;

            for(j=i-1; j<NEWpersonDBSize; j++)
            {
                // printf(" %d %d \n ",i,j);
                strcpy(NEWpersonsDB[j].nome,personsDB[i].nome);
                strcpy(NEWpersonsDB[j].cod_postal,personsDB[i].cod_postal);
                strcpy(NEWpersonsDB[j].datanascimento,personsDB[i].datanascimento);
                strcpy(NEWpersonsDB[j].freguesia,personsDB[i].freguesia);
                strcpy(NEWpersonsDB[j].morada,personsDB[i].morada);
                strcpy(NEWpersonsDB[j].nif,personsDB[i].nif);
                // printf(" %s %s--- \n",NEWpersonsDB[j].nome,personsDB[i].nome);
                // printf(" %s %s *** %s \n",NEWpersonsDB[j].nome,personsDB[i-1].nome,personsDB[i].nome);
                i++;

            }
            goto label;

        }
        strcpy(NEWpersonsDB[i].nome,personsDB[i].nome);
        strcpy(NEWpersonsDB[i].cod_postal,personsDB[i].cod_postal);
        strcpy(NEWpersonsDB[i].datanascimento,personsDB[i].datanascimento);
        strcpy(NEWpersonsDB[i].freguesia,personsDB[i].freguesia);
        strcpy(NEWpersonsDB[i].morada,personsDB[i].morada);
        strcpy(NEWpersonsDB[i].nif,personsDB[i].nif);

        //printf("%s  %s \n",NEWpersonsDB[i].nome,personsDB[i].nome);

        if((i+1)==(*pSize)-1 &&  strcmp(personsDB[i+1].nome,teste)!=0)
        {
            goto notfound;
        }

    }

notfound:
    printf("Pessoa nao registada!\n");
    return personsDB;



label:

    printf("Remocao concluida! \n");
    (*pSize)=NEWpersonDBSize;


//printf(" %d \n",NEWpersonDBSize);
//    for(i=0;i<NEWpersonDBSize;i++){
//        printf(" %s \n",NEWpersonsDB[i].nome);
//
//    }

    free(personsDB);


    //falta fazer a atribuição ou apontamento da DB original para a DB nova originada pela remoção da antiga.
    return NEWpersonsDB;

}

 /**
 * Exporta a BD para ficheiro txt
 *
 *
 *  @param StringElementsArray*  aux o nosso array de elementos
 *  @param int    Size tamanho do nosso Array
 *  @param
 *
 *
 *
 */

void exportaMSD(StringElementsArray*  aux,int size)
{

    // printf("\n---%s----\n",aux->str[2]);
    char nome[]="MSD";

    FILE *f=NULL;
    strcat(nome,".txt");
    f = fopen(nome, "w");

    int i = 0;
    if (f != NULL)
    {
        fprintf(f,"ORDENACAO NOMES MSD\n",personDBSize);
        while (i < personDBSize)
        {
            fprintf(f,"%s\n",aux->str[i]);
            i++;
        }
        fclose(f);
    }

    printf("\n Ficheiro %s criado!!!! \n",nome);

    char c;

    printf(" Pression \"f\" para voltar ao menu!\n");
    getchar();

    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }


}


 /**
 * Exporta a BD para ficheiro txt
 *
 *
 *  @param pessoa*      personsDB a nossa BD
 *  @param int    personDBSize tamanho da nossa BD
 *  @param char      nome string aux que trás o nome do ficheiro a exportar
 *
 *
 *
 */

//permite gravar e exportar um ficheiro txt de uma DB criada
void writeDB(pessoa * personsDB,int personDBSize,char nome[])
{

    FILE *f=NULL;
    strcat(nome,".txt");
    f = fopen(nome, "w");

    int i = 0;
    if (f != NULL)
    {
        fprintf(f,"%d\n",personDBSize);
        while (i < personDBSize)
        {
            fprintf(f,"%s;%s;%s;%s;%s\n",personsDB[i].nif,personsDB[i].nome,personsDB[i].datanascimento,personsDB[i].cod_postal,personsDB[i].freguesia);
            i++;
        }
        fclose(f);
    }

    printf("\n Ficheiro %s criado!!!! \n",nome);

    char c;

    printf(" Pression \"f\" para voltar ao menu!\n");

    c=getchar();
    if(c=='f')
    {
        menu(personsDB,personDBSize);
    }

}



/**
 *  Add just one person to our BD
 *
 *  @param char      nif string que vai receber o nif
 *  @param char      nome string que vai receber o nome
 *  @param char      data string que vai receber o data
 *  @param char      cod_postal string que vai receber o codg_postal
 *  @param char      freguesia string que vai receber a freguesia
 *
 *  @return da nova struct pessoa criada
 */

// Função para criar nova pessoa.

pessoa createnewperson(char nif[], char nome[], char data[], char morada[],char cod_postal[],char  freguesia[])
{
    // add a new person
    pessoa p= {"","","",""};
    strcpy(p.nif,nif);
    strcpy(p.nome,nome);
    strcpy(p.freguesia,freguesia);
    strcpy(p.cod_postal,cod_postal);
    strcpy(p.morada,morada);
    strcpy(p.datanascimento,data);

    personsDB = addPerson2PersonArray(personsDB, personDBSize, &p);
    personDBSize = personDBSize + 1;

    //printPerson(&p);

    return p;

}





/**
 *  Prints information about one person in console
 *
 *  @param person person to print
 */
void printPerson(pessoa * person)
{
    printf("NIF: %s\nNome: %s\nData de nascimento: %s\nFreguesia: %s\n",person->nif,person->nome,person->datanascimento,person->freguesia);
}

/**
 *  Read file with person's data and stores it in array
 *
 *  @param filename name of the file with data to load
 *  @param n        number of pessoa records that were read
 *
 *  @return pointer to pessoa array created
 */
pessoa * readFilePerson(char * filename, int * n)
{
    FILE * fp;
    pessoa * personsArray;
    char line[LINEMAXSIZE]; ///< esta variável será usada para guardar um parágrafo lido dum ficheiro de texto de pessoas
    int i = 0;
    fp = fopen(filename, "r");
    if (fp != NULL)
    {
        fscanf(fp,"%d\n", n);
        personsArray = newPersonArray((*n));
        while (!feof(fp) && i < (*n))
        {
            fgets(line, LINEMAXSIZE, fp);
            parseLine2Person(line, &personsArray[i]);
            i++;
        }
        fclose(fp);
    }
    else return 0;   // error readind file
    return personsArray;
}
/**
 *  Parses one line/paragraph from the ;-separated text file
 *  and fills the fields of variable person of type struct pessoa
 *
 *  @param line   (input) null terminated string with information about a person
 *  @param person (output) struct of type pessoa filled with info about the person
 */
void parseLine2Person(char * line, pessoa * person)
{
    char * field_separator = ";\n"; // ";" and "\n" are the field separators
    char * field_person;
    field_person = strtok(line, field_separator);
    strcpy(person->nif,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->nome,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->datanascimento,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->morada,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->cod_postal,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->freguesia,field_person);
}

/**
 *  Read file with person's family data, TO DO: change function prototype!
 *
 *  @param filename name of the file
 *
 *  @return number of persons read or error code (-1)
 */
int readFilePersonFamily(char * filename)
{
    FILE * fp;
    char line[LINEMAXSIZE];
    int i = 0, n;
    fp = fopen(filename, "r");
    if (fp != NULL)
    {
        fscanf(fp,"%d\n", &n);
        while (!feof(fp) && i < n)
        {
            fgets(line, LINEMAXSIZE, fp);
            processLine2PersonFamily(line);
            i++;
        }
        fclose(fp);
    }
    else return -1;   // error reading file
    return n;
}

/**
 *  Parses line from person family text file
 *
 *  @param line (input) null terminated string with information about a person's relatives
 */
void processLine2PersonFamily(char * line)
{
    char * field_separator = ";\n"; // ";" and "\n" are the field separators
    char * field_person;
    char nif1[10], nif2[10];
    int num_relatives, i=0;
    field_person = strtok(line, field_separator);
    strcpy(nif1,field_person);
    printf("\nNIF da pessoa: %s.",nif1);
    field_person = strtok(NULL, field_separator);
    num_relatives = atoi(field_person);
    printf(" Numero de familiares: %d. Lista dos seus NIFs: ",num_relatives);
    while (i < num_relatives)
    {
        field_person = strtok(NULL, field_separator);
        strcpy(nif2,field_person);
        printf("%s; ",nif2);
        i++;
    }
}


/**
 *  Concatenate / joins two pessoa arrays. Second array can be static or dynamic allocated.
 *
 *  @param personsArrayBase         personsArrayBase description
 *  @param personsArrayBaseSize     personsArrayBaseSize description
 *  @param personsArray2            personsArray2 description
 *  @param personsArray2Size        personsArray2Size description
 *  @param isArray2DynamicAllocated boolean value isArray2DynamicAllocated can be 1 (true) or 0 (false)
 *
 *  @return <#return value description#>
 */
pessoa * concatPersonArrays(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * personsArray2, int personsArray2Size, int isArray2DynamicAllocated)
{
    personsArrayBase = realloc(personsArrayBase, (personsArrayBaseSize + personsArray2Size) * sizeof(pessoa));
    memcpy(&personsArrayBase[personsArrayBaseSize], personsArray2, personsArray2Size * sizeof(pessoa));
    if (isArray2DynamicAllocated != 0)
    {
        freePersonArray(personsArray2);
    }
    return personsArrayBase;
}

/**
 *  Add just one person to the array. The person (argument person) must be statically declared
 *
 *  @param personsArrayBase     personsArrayBase description
 *  @param personsArrayBaseSize personsArrayBaseSize description
 *  @param person               person to be added to the end of the array
 *
 *  @return <#return value description#>
 */
pessoa * addPerson2PersonArray(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * person)
{
    return concatPersonArrays(personsArrayBase, personsArrayBaseSize, person, 1, 0);
}

/**
 *  Creates a new dynamic array of persons with size N
 *
 *  @param N size of array to be dynamically created
 *
 *  @return pointer to new array person created
 */
pessoa * newPersonArray(int N)
{
    return (pessoa *) malloc(sizeof(pessoa) * N);
}

/**
 *  Frees the dynamic array p from the memory (deletes the array)
 *
 *  @param p p description
 */
void freePersonArray(pessoa * p)
{
    free(p);
}




