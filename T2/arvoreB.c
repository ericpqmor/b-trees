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


//1.Funções relacionadas a criação de nós e arvoresB, e também em relação a liberação das arvoresB e dos nós


/**
FUNCAO: Cria um novoNOH que será ultiizado na manipulação da ArvoreB, o noh, ao ser criado contém 0 elementos, nao contém um pai, e todos os seus filhos, devem
ser alocados, como NULL, para evitar erros de manipulação, o parametro passado, representa a ordem da arvoreB, que é importante para a construção de um nó,
com as devidas adequações.
*/
Noh* NovoNOH(int ordem){

    //Aloca memoria para o noh
    Noh *novo = (Noh*) malloc(sizeof(Noh));

    //Aloca o vetor de chaves, e o vetor de filhos, seguindo as restrições
    novo->info = (int *) malloc(sizeof(int *) * (ordem * 2 - 1));
    novo->filhos = (Noh **) malloc(sizeof(Noh *) * (ordem * 2));

    //Seta o apontador pai como NULL
    novo->pai = NULL;
    
    //Inicializar elementos como zero
    novo->elementos = 0;

    //Todos os filhos recebem NULL, para auxiliar na manipulação
    for (int i = 0; i < (ordem * 2); i++) {
        novo->filhos[i] = NULL;
    }

    //Retorna um apontador para noh
    return novo;
}

/**
FUNCAO: Cria a arvore B recebendo o parametro ordem, que representa a ordem da arvore B, caso essa ordem for maior que 511, a arvore não é criada, então,
a memoria é alocada, e cria-se um nó raiz para a arvore.
*/
ArvoreB* CriaArvoreB(int ordem){

    //Tamanho máximo
    if(ordem > ORD_MAX)
        return NULL;

    //Aloca espaço para a arvoreB
    ArvoreB *arvore_nova = (ArvoreB*)malloc(sizeof(ArvoreB));

    //Seta a ordem da arvoreB
    arvore_nova->ordem = ordem;

    //Cria o noh raiz, que inicialmente está vazio
    arvore_nova->raiz = NovoNOH(ordem);

    //Retorna um apontador para arvore
    return arvore_nova;
}

/**
FUNCAO:Desaloca a memoria alocada para a arvore e seus NOHS
*/
ArvoreB *liberaArvore(ArvoreB *arvore) {
    
    //Atribui a variavel local a ordem da arvore
    int ordem = arvore->ordem;

    //O apontador para noh t recebe o noh raiz
    Noh *t = arvore->raiz;

    //Liberação da arvore, liberando todos os nós possíveis
    if (arvore->raiz != NULL) {
        for (int i = 0; i <  ordem * 2; i++) {
            t->filhos[i] = liberaNOH(t->filhos[i], ordem);
        }
        free(t->info);
        free(t->filhos);
        free(t);

        free(arvore);
    }

    //Retorna NULL
    return NULL;
}

/**
FUNCAO:Libera o NOH
*/
Noh* liberaNOH(Noh *t,int ordem){

    //Caso o nó não for vazio, libera de forma recursiva os filhos
    if (t != NULL) {
        for (int i = 0; i < ordem * 2; i++) {
            t->filhos[i] = liberaNOH(t->filhos[i], ordem);
        }

        free(t->info);
        free(t->filhos);
        free(t);
    }

    //Retorna NULL
    return NULL;
}

//2. Funções relacionadas a impressão da arvoreB e de seus respectivos nós

/**
FUNCAO: A impressao da arvore é feita na vertical, com a menor chave do nó, na parte debaixo do nó, ou seja, o nó que contém as chaves 1,2,3 é representado da 
seguinte forma:

    3
    2
    1
*/
void ImprimeArvore(Noh *noh, int nivel){
    
    //O noh passado é a raiz, e então verifica-se se a raiz não é NULL
    if (noh != NULL) {
        char indentacao[10] = "";
        for (int i = 0; i < nivel; i++) {
            strcat(indentacao, "\t");
        }

        for (int i = noh->elementos; i > 0; i--) {
            ImprimeArvore(noh->filhos[i], nivel + 1);
            printf("%s", indentacao);
            printf("%5d\n", noh->info[i - 1]);
        }
        ImprimeArvore(noh->filhos[0], nivel + 1);
    }

}
/**
FUNCAO:Impressão de um nó, que é feita para exibir o noh que a chave x foi inserida,ou o noh que a chave y, está inserida, na operação de busca.
*/
void ImprimeNOH(Noh *noh){

    //Imprime o noh na horizontal caso este não for NULL
    if (noh != NULL) {
        for (int i = 0; i < noh->elementos; i++) {
            printf("%5d", noh->info[i]);
        }
        printf("\n");
    }
}

//3.Funções relacionadas a busca em nós

/**
FUNCAO: Busca binária em um noh
*/
int BuscaBinaria(int chave,Noh *noh){

    //Sets da busca binária, p = inicio, r = fim e q=media
    int p = 0;
    int r = noh->elementos;
    int q = r/2;

    //Laço principal da busca binária
    while(q != noh->elementos && chave != noh->info[q] && p < r){
        if(chave > noh->info[q])
            //Vai para direita
            p = q+1;
        else
            //Vai para a direita
            r = q;
        q = (p+r)/2;

    } 

    //Retorna a posição em que a chave deveria estar inserida no noh
    return q;
}

/**
FUNCAO: Busca recursiva de uma chave na arvoreB, que indica em qual noh, a chave deveria estar, util para a inserção
*/
Noh* BuscaNohR(Noh *noh,int chave){

    //Acha a posiçao que a chave está ou deveria estar inserida
    int pos = BuscaBinaria(chave, noh);

    //No caso de não existir o noh filho, ou achar a chave retorna o noh
    if (noh->filhos[pos] == NULL || (pos < noh->elementos && chave == noh->info[pos])) {
        return noh;
    }
    //Caso nao encontre, realiza uma chamada recursiva, com o filho do noh
    else {
        return BuscaNohR(noh->filhos[pos], chave);
    }
}

/**
FUNCAO: Busca por uma chave na arvoreB, como ultiliza-se da busca recursiva, após o retorno do noh, que a chave deve estar inserida, verifica se a chave está
realmente inserida, utlilzando-se da busca binária em um Noh, caso a chave esteja inserida no NOH, então o indice que ela está é passado por referencia, e o 
noh é retornado, caso a chave não seja encontrada, é retornado um ponteiro NULL
*/
Noh* BuscaArvoreB(ArvoreB *arvore,int alvo,int *i){

    //Busca o noh em que a chave está ou deveria estar inserida
    Noh *noh = BuscaNohR(arvore->raiz,alvo);

    //Com o noh retornado, realiza-se uma busca binária para descobrir qual a suposta posição da chave
    int pos = BuscaBinaria(alvo,noh);

    //Verifica se a chave está inserida
    if(noh->info[pos] == alvo){

        //indice passado por parametro
        *i = pos;

        //Retorna o nó
        return noh;
    }
    
    //Retorna NULL
    return NULL;

}

//4.Funções relacionadas a inserção de chaves em nós folhas da arvore binária

/**
FUNCAO: Essa função faz a divisão do NOH, no caso dele estar cheio, para isso, particiona-se o noh P, e adiciona-se a chave e o ponteiro pt, após o final da 
execução dessa função, a chave terá sido inserida no local correto, e um novo noh Q é criado como resultado do partcionamento, caso uma nova raiz deva ser 
criada, então, W é criada, para particionar a raiz
 */
void DivideNOH(Noh *P, int d, int pos, int chave, Noh *pt) {
    
    //noh_dir se refere ao nó da direita, e P se refere ao nó da esquerda


    // Prepara noh_dir
    Noh *noh_dir = NovoNOH(d);

    //Ajusta i e j corretamente
    int i = d * 2 - 1;
    int j = d -1;

    

    //Laço que faz a partição das chaves entre noh_dir e P
    while (j >= 0) {

        //Move as chaves que estavam em P para noh_dir
        if (j != pos - d - 1) { 
            noh_dir->info[j] = P->info[i];
            noh_dir->filhos[j + 1] = P->filhos[i + 1];
            i--;
        }
        //Insere em noh_dir a chave
        else {
            noh_dir->info[j] = chave;
            noh_dir->filhos[j + 1] = pt;
        }


        if (noh_dir->filhos[j + 1] != NULL) {
            noh_dir->filhos[j + 1]->pai = noh_dir;
        }
        j--;

    }

    //Elementos que contém em Q
    noh_dir->elementos = d-1;


    //Manipula P
    if (pos <= d) {
        P->elementos = d;
        Insere(P, d, pos, chave, pt); // A inserção faz com que  o número de chaves aumente para d+1
    }

    // Processa X, caso seja raiz, processa o noh superior
    if (P->pai == NULL) {
        Noh *X = NovoNOH(d);
        X->filhos[0] = P;
        P->pai = X;
    }
    // Chave d de P sobe para o pai X
    Insere(P->pai, d, -1, P->info[d], noh_dir);

    //Após a partição ajusta os filhos dos nos, a partir do noh d+1, vai para o noh Q, e oque está antes do filho d+1, permanece em P
    int a=0;
    int b=d+1;
    while(b <= 2*d -1){
        noh_dir->filhos[a] = P->filhos[b];
        P->filhos[b] = NULL;
        a++;
        b++;
    }

    //Se o primeiro ponteiro de filhos for != NULL, então ajusta-se o ponteiro do pai de noh_dir pelo primeiro ponteiro apontado por filhos
    if (noh_dir->filhos[0] != NULL)
        noh_dir->filhos[0]->pai = noh_dir;

    //Com a inserção da chave d no nó X, o numero de chave de P, diminui para d
    P->elementos = d;
}

/**
FUNCAO:Insere a chave e o seu ponteiro a direita em uma posição do noh, de uma arvoreB, o parametro d é a ordem da arvore
 */
void Insere(Noh *no, int d, int pos, int chave, Noh *pt) {
    
    //Caso a posição seja -1, isso significa que a posição é invalida, logo deve-se procurar no noh, a posição da chave
    if (pos == -1) {
        pos = BuscaBinaria(chave, no);
    }

    //Inserção caso tenha espaço no nó folha, oque resulta em uma inserção simples
    if (no->elementos < 2 * d - 1) {

        //Ordenação do noh, de acordo com o valor de pos, que representa a posição que a chave deveria estar
        for (int i = no->elementos; i > pos; i--) {
            no->info[i] = no->info[i - 1];
            no->filhos[i + 1] = no->filhos[i];
        }

        //Guarda a chave na posição pos do nó
        no->info[pos] = chave;

        //Coloca o ponteiro pt como filho na posição pos+1
        no->filhos[pos + 1] = pt;

        //Caso esse ponteiro não for NULL, então seu campo pai, aponta para no
        if (pt != NULL) {
            pt->pai = no;
        }

        //Incrementa-se em um o número de elementos no nó
        no->elementos++;
    } 

    //Caso o nó estiver cheio, é necessário chamar a função DivideNoh para particionar o noh, e poder inserir a chave corretamente
    else 
        DivideNOH(no, d, pos, chave, pt);
    
}

/**
FUNCAO: Inserção geral na arvore, calculando o indice que a chave foi inserida, e retornando o noh em que foi inserida, caso a chave esteja repetida,
então retorna-se NULL
 */
Noh* InsereArvoreB(ArvoreB *arvore,int chave,int *i) {

    //Pega a ordem da arvore
    int ordem = arvore->ordem;

    //Caso a raiz não for NULL, isso significa que o noh raiz não está vazio
    if (arvore->raiz != NULL) {

        //Busca a chave, para verifica se esta já foi inserida
        Noh *no = BuscaNohR(arvore->raiz, chave);
        int pos = BuscaBinaria(chave, no);

        //Caso a chave não exista no noh, ela é inserida
        if (pos == no->elementos || chave != no->info[pos]){
            Insere(no, ordem, pos, chave, NULL);

            //Caso a inserção tenha criada uma nova raiz, ajusta-se
            if (arvore->raiz->pai != NULL)  // Inserção riou uma nova raiz
                arvore->raiz = arvore->raiz->pai;
        }

        //Caso a chave já tenha sido inserida, retorna-se NULL
        else
            return NULL;
        
        
    }

    //Caso a raiz estiver vazia, insere manualmente a chave, e  o número de elementos se torna 1
    else {
        arvore->raiz->info[0] = chave;
        arvore->raiz->elementos = 1;
    }

    

    //Retornar o noh em que a chave foi inserida junto com o indice
    int indice;

    Noh *no = BuscaArvoreB(arvore,chave,&indice);

    //Salva o indice
    *i = indice;
    return no;
    
}

//5.Função relacionada a inserção da opção, inserção,busca, mostrar a arvore ou Sair

/**
FUNCAO:Apenas mostra as opções, pode-se inserir as letras tanto maiusculas, quanto minusculas
*/
char menu(){

    //Inicializa-se opção com qualquer valor arbitrário diferente de S,B,I,M
    char opcao = 'T';

    //Inicia o contador
    int i=0;

    //Laço principal de inserção
    while(opcao != 'S' && opcao != 'B' && opcao != 'I' && opcao != 'M'){

        //Caso tenha sido digitado uma operação inválida, então apresenta-se essa mensagem
        if(i > 0)
            printf("'%c' eh uma operacao invalida, digite novamente\n",opcao);
        
        //Mensagem principal
        printf("--------------------------------\n");
        printf("I) Insercao\nB) Busca\nM) Mostrar arvoreB\nS) Sair\n");
        printf("--------------------------------\nDigite sua opcao: ");

        //Entrada
        scanf("%*c%c",&opcao);

        //Transforma em maiuscula, logo, caso seja digitado i ele transforma em I
        opcao = toupper(opcao);

        //Incrementa o contador, que caso ocorra um novo laço, representa que a opção inválida foi digitada
        i++;
    }

    //Retorna a caractere de opção
    return opcao;
}
