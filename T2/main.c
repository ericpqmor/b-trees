/**
NOME: Gabriel Meirelles Carvalho Orlando
RA: 790728

NOME: Eric Pereira Queiroz Moreira		
RA: 799662

CURSO: Ciencia da Computação
DATA: 19/10/2021
FLAGS: -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
*/

#include "arvoreB.h"

int main(){

    //Declarações globais
    ArvoreB *arvore;
    Noh *aux;
    char opcao;
    int d;

    //Entrada da ordem da arvore
    printf("Digite a ordem (d) da árvore B: ");
    scanf("%d", &d);

    //Cria a arvoreB
    arvore = CriaArvoreB(d);

    //Caso tenha algum problema na alocação de memoria, ou a ordem seja maior que 10
    if(!arvore){
        printf("A arvore não foi criada com sucesso, finalizando a execução...\n");
        exit(1);
    }

    //Laço principal de entrada
    while(opcao != 'S'){
        
        //Declarações locais
        int indice;
        int chave;

        //Entrada das opções
        opcao = menu();

        //Busca
        if(opcao == 'B'){

            //Entrada
            printf("Digite a chave que deseja ser buscada:");
            scanf("%d",&chave);

            //Busca pela chave
            aux = BuscaArvoreB(arvore,chave,&indice);

            //Caso a chave seja encontrada
            if(aux != NULL){

                //Saída
                printf("Chave encontrada no indice %d do seguinte noh:\n",indice);
                ImprimeNOH(aux);
            }

            //Caso não encontre o nó
            else
                //Saída
                printf("CHAVE NÃO ENCONTRADA!\n");
            
        }

        //Inserção
        else if(opcao == 'I'){

            //Entrada
            printf("Digite a chave que deseja ser inserida:");
            scanf("%d",&chave);
            
            //Inserção na árvoreB
            aux = InsereArvoreB(arvore,chave,&indice);

            //Caso insira corretamente
            if(aux != NULL){
            
                //Saída
                printf("Chave inserida no indice %d do seguinte noh:\n",indice);
                ImprimeNOH(aux);
            }

            //Caso a chave já estja inserida
            else
                //Saída
                printf("Chave %d ja existe, digite outra chave\n",chave);
        }

        //Impressão da árvore
        else if(opcao == 'M'){

            //Caso a arvore não tenha elementos, não há oque imprimir
            if(arvore->raiz->elementos == 0)
                printf("A arvore eh vazia, impossivel de ser exibida\n");

            //Caso tenha, imprime a árvoreB
            else
                ImprimeArvore(arvore->raiz,0);
        }

        //Encerra a execução
        else 
            printf("Encerrando as operações...\n");
    }

    //Libera a memória alocada para a árvore
    arvore = liberaArvore(arvore);

    return 0;
}

//gcc -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm main.c arvoreB.c arvoreB.h -o 1
