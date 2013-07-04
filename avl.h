
#ifndef _AVL_
#define _AVL_

#include "iterator.h"

typedef enum BalanceFactor
{ L, E, R } BalanceFactor;

typedef struct _treenode_
{
  void *key;
  void *value;
  BalanceFactor bf;
  struct _treenode_ *super;
  struct _treenode_ *left;
  struct _treenode_ *right;
} *treenode, TreeNode;

typedef struct _avl_
{
  int (*keyCmp) (void *, void *);
  unsigned int size;
  treenode root;
} *avl, Avl;

#endif

 /*FUNCOES*/
/*CRIA UMA NOVA AVL*/
avl
createAvl (int (*keycmp) (void *, void *));

/*APAGA UMA AVL*/
void deleteAvl (avl tree);

/*INSERE NA ARVORE*/
int insertAvl (avl tree, void *key,
	       void *value);

/*REMOCAO DA AVL RETORNA 0 SE OK 1 SE CHAVE NAO EXISTE*/
int removeAvl (avl tree, void *key,
	       void **value,
	       void (*del) (void *));

/*DEVOLVE UM ELEMENTO DA AVL*/
int getAvl (avl tree, void *key,
	    void **value);

/*ALTURA DA ARVORE*/
unsigned int hightAvl (avl tree);

/*TAMANHO DA ARVORE - NUMERO DE NODOS*/
unsigned int sizeAvl (avl tree);

/*TRAVESSIA INORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int inOrderAvl (avl tree,
		void (*fun) (void *));

/*TRAVESSIA PREORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int preOrderAvl (avl tree,
		 void (*fun) (void *));

/*TRAVESSIA PREORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int posOrderAvl (avl tree,
		 void (*fun) (void *));

/*TODAS AS CHAVES DA AVL NUM ITERADOR-REFERENCIA*/
iterator avlKeys (avl tree);

/*TODOS OS DADOS DA AVL NUM ITERADOR-REFERENCIA*/
iterator avlValues (avl tree);
