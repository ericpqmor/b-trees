/**
NOME: Gabriel Meirelles Carvalho Orlando
RA: 790728

NOME: Eric Pereira Queiroz Moreira		
RA: 799662

CURSO: Ciencia da Computação
DATA: 19/10/2021
FLAGS: -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
*/

//Bibliotecas ultilizadas
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Ordem máxima da árvore
#define ORD_MAX 10


//Struct noh
typedef struct noh{

    struct noh *pai;
    int *info;
    struct noh **filhos;
    int elementos;

}Noh;

//Struct arvore
typedef struct arvore{

    int ordem;
    Noh *raiz;
    
}ArvoreB;


//Cria um nó
Noh* NovoNOH(int ordem);

//Cria uma arvoreB
ArvoreB* CriaArvoreB(int ordem);

//Libera a memoria alocada de uma arvoreB
ArvoreB *liberaArvore(ArvoreB *arvore);

//Libera a memoria alocada para um noh
Noh* liberaNOH(Noh *t,int ordem);

//Busca binária no nó
int BuscaBinaria(int chave,Noh *noh);

//Busca recursiva dos nós da arvoreB
Noh* BuscaNohR(Noh *noh,int chave);

//Busca uma chave em uma árvoreB
Noh* BuscaArvoreB(ArvoreB *arvore,int alvo,int *i);


//Divide um nó em dois
void DivideNOH(Noh *P, int d, int pos, int chave, Noh *pt);

//Insere na árvoreB
void Insere(Noh *no, int d, int pos, int chave, Noh *pt);

//Inserção geral da arvoreB
Noh* InsereArvoreB(ArvoreB *arvore,int chave,int *i);

//Menu de opções
char menu();

//Imprime uma arvoreB
void ImprimeArvore(Noh *a, int nivel);

//Imprime um noh
void ImprimeNOH(Noh *noh);