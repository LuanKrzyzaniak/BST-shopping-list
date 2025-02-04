/*
Alunos: Luan Alecxander Krzyzaniak / Bernardo Flores Dalla Rosa
Professor(a): Andrei / Andressa
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

// Struct que representa um item de uma lista de compras armazenada em uma arvore binaria de busca
struct item {
	char produto[50];
	int quantidade;
     struct item  *esquerdo; 
     struct item  *direito;
};
typedef struct item Item;

// Apresenta o primeiro menu da aplicação e retorna a opção selecionada
int menu1()
{
     int op = 0;
     printf("\nMenu principal\n");
     printf("\n %d - Gerenciar lista de compras A", 1);
     printf("\n %d - Gerenciar lista de compras B", 2);
     printf("\n %d - Visualizar itens duplicados", 3);
     printf("\n %d - Sair do programa",EXIT);
     printf("\n\nDigite a opção: ");
     scanf("%d",&op);
     return op;
}

// Apresenta o segundo menu da aplicação e retorna a opção selecionada
int menu2()
{
    int op = 0;
     printf("\n %d - Inserir item", 1);
     printf("\n %d - Consultar item", 2);
     printf("\n %d - Atualizar item", 3);
     printf("\n %d - Listar itens", 4);
     printf("\n %d - Deletar item", 5);
     printf("\n %d - Retornar para o menu principal", EXIT);
     printf("\n\nDigite a opção: ");
     scanf("%d",&op); 
    return op;
}
// FUNÇÕES AUXILIARES -----------------------------------------------------------------------------------------------------------------
// [INSERT] Criar item para insert
Item *criarItem(){
     char produto[50];
     int quantidade;
     char temp;

     printf("\nPor favor, informe:\n\tNome do produto: ");
     scanf("\n%[^\n]", &produto);
     scanf("%c",&temp); // Dar clear no scanf pra não bugar o menu
     printf("\tQuantidade do produto: ");
     scanf("%d", &quantidade);

     Item *aux;
     aux = malloc(sizeof(Item));
     strcpy(aux->produto, produto);
     aux->quantidade = quantidade;
     aux->esquerdo = aux->direito = NULL;
     printf("\nProduto '%s' criado com '%d' quantidade.", aux->produto, aux->quantidade);
     return aux;
}

// [TESTE] Função para criar os itens de teste
Item *criarTeste(char nome[50], int quantidade){
     Item *aux;
     aux = malloc(sizeof(Item));
     strcpy(aux->produto, nome);
     aux->quantidade = quantidade;
     aux->esquerdo = aux->direito = NULL;
     return aux;
}

// [DELETE] Encontrar a maior folha da esquerda para
Item *maiorEsquerda(Item *raiz)
{
    Item *aux = raiz;
    while (raiz && raiz->direito != NULL) raiz = raiz->direito;
    return raiz;
}

// [INTERSECT] Transforma a BST em uma lista linear.
void bstLinear(Item *raiz){
     // Caso base, NULL ou folha
          if (raiz == NULL || raiz->direito && raiz->esquerdo == NULL) return;
     // Trasforma a esquerda da raiz em direita
     if (raiz->esquerdo != NULL){
          // Se move pra direita
          bstLinear(raiz->esquerdo);
          // Guarda a raiz direita
          Item *auxDireito = raiz->direito;
          raiz->direito = raiz->esquerdo;
          raiz->esquerdo = NULL;
          // Acha a posição pra inserir
          Item *aux = raiz->direito;
          while (aux->direito != NULL) aux = aux->direito;
          aux->direito = auxDireito;
     }
     bstLinear(raiz->direito);
}

Item *montarLista(Item *raiz, char produto[50])
{
     // Casos base.
     if (raiz == NULL){ // Chegou na raiz (insere)
          Item *aux;
          aux = malloc(sizeof(Item));
          strcpy(aux->produto, produto);
          aux->quantidade = 0;
          aux->direito = NULL;
          aux->esquerdo = NULL;
          return aux;
     }
     // Recursão para percorrer a árvore.
     raiz->direito = montarLista(raiz->direito, produto);
}

// [INTERSECT] Cria uma lista de intersecção.
Item *criarLista(Item *listaA, Item *listaB, Item *listaNova){
     Item *auxA = NULL;
     Item *auxB = NULL;
     for (auxA = listaA; auxA != NULL; auxA = auxA->direito){
          for (auxB = listaB; auxB != NULL; auxB = auxB->direito){
               if (strcmp(auxA->produto, auxB->produto) == 0){
                    listaNova = montarLista(listaNova, auxB->produto);
               }
          }
     }
     return listaNova;
}

// [INTERSECT] Cria uma lista de intersecção.
void printarLista(Item *listaNova){
     Item *aux;
     for (aux = listaNova; aux != NULL; aux = aux->direito){
          printf("\n Produto: '%s'", aux->produto);
     }
}

// FUNÇÕES PRINCIPAIS -----------------------------------------------------------------------------------------------------------------
// Permite o cadastro de um item (caso o produto ainda não exista) em uma lista de compas
Item *insert(Item *raiz, Item *aux)
{
     // Casos base.
     if (raiz == NULL){ // Chegou na raiz (insere)
          printf("\nO produto foi inserido com sucesso.\n");
          return aux;
     }
     // Recursão para percorrer a árvore.
     if (strcmp(aux->produto, raiz->produto) > 0){
          raiz->direito = insert(raiz->direito, aux);
     } else if (strcmp(aux->produto, raiz->produto) < 0){
          raiz->esquerdo = insert(raiz->esquerdo, aux);
     } else{
          printf("\nO produto já está na lista.\n");
     }
     return raiz; 
}

// Permite consultar se um item está em uma lista de compras
void query(Item *raiz, char produto[50])
{
     if (raiz == NULL){
          printf("\nO produto não está na lista.\n");
          return;
     }
     if (strcmp(raiz->produto,produto) == 0){
          printf("\nProduto encontrado!");
          printf("\nProduto: '%s'\tQuantidade: '%d'\n", raiz->produto, raiz->quantidade);
          return; 
     }
     else if (strcmp(produto,raiz->produto) > 0){
          query(raiz->direito, produto);
     } 
     else{
          query(raiz->esquerdo, produto);
     }
}


// Permite a atualização da quantidade de um produto (caso exista) na lista de compras
void update(Item *raiz, char produto[50])
{
     int novaQuantia;
     if (raiz == NULL){
          printf("\nO produto não está na lista.\n");
     }
     if (strcmp(raiz->produto,produto) == 0){
          printf("\nProduto encontrado!");
          printf("\nProduto: '%s'\tQuantidade: '%d'\nDigite a nova quantia: ", raiz->produto, raiz->quantidade);
          scanf("%d", &novaQuantia);
          raiz->quantidade = novaQuantia;
          printf("\n Quantia alterada.\nProduto: '%s'\tQuantidade: '%d'\n", raiz->produto, raiz->quantidade);
     }
     else if (strcmp(produto,raiz->produto) > 0){
          update(raiz->direito, produto);
     } 
     else{
          update(raiz->esquerdo, produto);
     }
}

// Listar todos os itens da lista de compras em ordem alfabética;
void list(Item *raiz)
{
     if (raiz == NULL) return;

     list(raiz->esquerdo);
     printf("\nProduto: %s\t Quantia: %d", raiz->produto, raiz->quantidade);
     list(raiz->direito);
}

// Permite excluir um item de uma lista de compras
Item *delete(Item *raiz, char produto[50])
{
     Item *aux;
     // Caso não encontre o item
     if (raiz == NULL){
          printf("\nO produto %c não foi encontrado.", produto);
          return raiz;
     }
     // Recursão para percorrer a árvore
     if (strcmp(produto, raiz->produto) < 0){
          raiz->esquerdo = delete(raiz->esquerdo, produto);
     } else if (strcmp(produto, raiz->produto) > 0){
          raiz->direito = delete(raiz->direito, produto);
     } else { 
          // Produto encontrado
          // Caso produto não tenha filhos
          if (raiz->esquerdo == NULL){
               aux = raiz->direito;
               free(raiz);
               return aux;
          }
          else if (raiz->direito == NULL){
               aux = raiz->esquerdo;
               free(raiz);
               return aux;
          }
          // Caso o produto tenha dois filhos
          aux = maiorEsquerda(raiz->esquerdo);
          strcpy(raiz->produto, aux->produto);
          raiz->quantidade = aux->quantidade;
          raiz->esquerdo = delete(raiz->esquerdo, aux->produto);
     }
     return raiz;
}



void intersect(Item *raizA, Item *raizB)
{
     Item *listaA = raizA;
     Item *listaB = raizB;
     Item *listaNova = NULL;
     // 'Amassar' as árvores
     bstLinear(listaA);
     bstLinear(listaB);
     // Printar os produtos usando as listas
     listaNova = criarLista(listaA, listaB, listaNova);
     printarLista(listaNova);
     printf("\n");

}

// Programa principal
int main()
{
    int opcao1;
    int opcao2;
    Item *raizA = NULL;
    Item *raizB = NULL;
    char produto[50];

     // Produtos inseridos para teste
     Item *aux;
     raizA = criarTeste("Pepsi",10);
     raizA->esquerdo = criarTeste("Guarana",4);
     raizA->esquerdo->direito = criarTeste("Guarana-jesus",6);
     raizA->esquerdo->esquerdo = criarTeste("Coca-Cola",15);
     raizA->direito = criarTeste("Pureza",2);
     raizA->direito->direito = criarTeste("Zero",5);

     raizB = criarTeste("Portorrico",10);
     raizB->esquerdo = criarTeste("Licor",4);
     raizB->esquerdo->direito = criarTeste("Guarana-jesus",6);
     raizB->esquerdo->esquerdo = criarTeste("Catuaba",15);
     raizB->direito = criarTeste("Pureza",2);
     raizB->direito->direito = criarTeste("Rum",5);



     opcao1 = 0;
     while (opcao1 != EXIT)
     {
          opcao1 = menu1();
               
          switch(opcao1)
          {
               case 1 : // gerenciar lista de compras A
                    opcao2 = 0;
                    while(opcao2 != EXIT){
                         printf("\n-- Lista de Compras A --\n");
                         opcao2 = menu2();
                         switch(opcao2){ // operacoes sobre a arvore A
                              case 1 : // INSERIR
                                   printf("\nVocê escolheu inserir um item.");
                                   Item *aux = criarItem();
                                   raizA = insert(raizA, aux);
                                   printf("\nProduto '%s' quantidade '%d'", raizA->produto, raizA->quantidade);
                                   break;
                              case 2 : // CONSULTAR
                                   if (raizA == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu consultar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   query(raizA, produto);
                                   break;
                              case 3 : // ATUALIZAR
                                   if (raizA == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu atualizar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   update(raizA, produto);
                                   break;
                              case 4 : // LISTAR
                                   if (raizA == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\n--- LISTA A ---");
                                   list(raizA);
                                   printf("\n");
                                   break;
                              case 5 : // DELETE  
                                   if (raizA == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu deletar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   raizA = delete(raizA, produto);
                                   break;
                         }    
                    }
                    break;
               case 2 : // gerenciar lista de compras B
                    opcao2 = 0;
                    while(opcao2 != EXIT){
                         printf("\n-- Lista de Compras B --\n");
                         opcao2 = menu2();
                         switch(opcao2){ // operacoes sobre a arvore B
                              case 1 : // INSERIR
                                   printf("\nVocê escolheu inserir um item.");
                                   Item *aux = criarItem();
                                   raizB = insert(raizB, aux);
                                   printf("\nProduto '%s' quantidade '%d'", raizB->produto, raizB->quantidade);
                                   break;
                              case 2 : // CONSULTAR
                                   if (raizB == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu consultar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   query(raizB, produto);
                                   break;
                              case 3 : // ATUALIZAR
                                   if (raizB == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu atualizar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   update(raizB, produto);
                                   break;
                              case 4 : // LISTAR
                                   if (raizB == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\n--- LISTA B ---");
                                   list(raizB);
                                   printf("\n");
                                   break;
                              case 5 : // DELETE  
                                   if (raizB == NULL){
                                        printf("\nOpção inválida. A lista está vazia!\n");
                                        break;
                                   }
                                   printf("\nVocê escolheu deletar um produto. Digite o nome: ");
                                   scanf("%s", &produto);
                                   raizB = delete(raizB, produto);
                                   break;
                         }    
                    }
                    break;
               case 3 : // Visualizar itens duplicados
                    printf("\n-- Lista de itens duplicados --\n");
                    intersect(raizA, raizB);
                    break;

          }
     }
     return 0;
}