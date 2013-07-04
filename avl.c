
#include"avl.h"
#include<stdlib.h>


/*ROTACAO A ESQUERDA*/
static treenode
leftRotate (treenode tree)
{

  treenode aux;

  if (tree && tree->right)
    {
      aux = tree->right;
      tree->right = aux->left;
      aux->left = tree;

      aux->super = tree->super;
      tree->super = aux;

      if (tree->right)
	tree->right->super = tree;

      return aux;
    }
  else
    return tree;

}

/*ROTACAO A DIREITA*/
static treenode
rightRotate (treenode tree)
{

  treenode aux;

  if (tree && tree->left)
    {
      aux = tree->left;
      tree->left = aux->right;
      aux->right = tree;

      aux->super = tree->super;
      tree->super = aux;

      if (tree->left)
	tree->left->super = tree;
      return aux;
    }
  else
    return tree;
}

/*BALANCEAR A ESQUERDA*/
static treenode
leftBalance (treenode tree)
{

  if (tree && tree->left)
    {
      if (tree->left->bf == L)
	{
	  tree = rightRotate (tree);
	  tree->bf = E;
	  tree->right->bf = E;
	}
      else
	{
	  tree->left =
	    leftRotate (tree->left);
	  tree = rightRotate (tree);
	  switch (tree->bf)
	    {
	    case L:
	      tree->left->bf = E;
	      tree->right->bf = R;
	      break;
	    case E:
	      tree->left->bf = E;
	      tree->right->bf = E;
	      break;
	    case R:
	      tree->left->bf = L;
	      tree->right->bf = E;
	    }
	  tree->bf = E;
	}
    }
  else
    {
      tree = rightRotate (tree);
      tree->right->bf = E;
      tree->left->bf = E;
    }
  return tree;
}

/*BALANCEAR A DIREITA*/
static treenode
rightBalance (treenode tree)
{

  if (tree && tree->right)
    {
      if (tree->right->bf == R)
	{
	  tree = leftRotate (tree);
	  tree->bf = E;
	  tree->left->bf = E;
	}
      else
	{
	  tree->right =
	    rightRotate (tree->right);
	  tree = leftRotate (tree);
	  switch (tree->bf)
	    {
	    case L:
	      tree->left->bf = E;
	      tree->right->bf = R;
	      break;
	    case E:
	      tree->left->bf = E;
	      tree->right->bf = E;
	      break;
	    case R:
	      tree->left->bf = L;
	      tree->right->bf = E;
	    }
	  tree->bf = E;
	}
    }
  else
    {
      tree = rightRotate (tree);
      tree->left->bf = E;
      tree->right->bf = E;
    }

  return tree;
}

/*CRIA UMA NOVA AVL*/
avl
createAvl (int (*keycmp) (void *, void *))
{
  if (!keycmp)
    return NULL;
  else
    {
      avl tree = (avl) malloc (sizeof (Avl));
      if (!tree)
	return NULL;
      else
	{
	  tree->keyCmp = *keycmp;
	  tree->size = 0;
	  tree->root = NULL;
	  return tree;
	}
    }
}

/*FUNCAO AUXILIAR PARA APAGAR A ARVORE
 * NAO APAGA AS KEYS NEM OS VALUES*/
static void
treeDelAux (treenode tree)
{
  if (tree)
    {
      treeDelAux (tree->left);
      treeDelAux (tree->right);
      free (tree);
    }
}

/*APAGA UMA AVL */
void
deleteAvl (avl tree)
{
  treeDelAux (tree->root);
  free (tree);
}

/*INSERE NA AVL AUXILIAR*/
static treenode
treeInsAux (treenode tree, void *key,
	    void *value, int *h,
	    int (*cmp) (void *, void *))
{
  int sig;
  if (!tree)
    {

      treenode new;
      new =
	(treenode)
	malloc (sizeof (TreeNode));

      if (new)
	{
	  new->key = key;
	  new->value = value;
	  new->bf = E;
	  new->super = NULL;
	  new->left = NULL;
	  new->right = NULL;
	  *h = 0;
	  return new;
	}
      else
	{
	  *h = 2;
	  return NULL;
	}

    }
  else
    {
      sig = cmp (key, tree->key);

      if (sig < 0)
	{

	  tree->left =
	    treeInsAux (tree->left, key,
			value, h, cmp);

	  if (!(*h))
	    {

	      tree->left->super = tree;

	      switch (tree->bf)
		{
		case L:
		  tree = leftBalance (tree);
		  tree->bf = E;
		  *h = -1;
		  break;
		case E:
		  tree->bf = L;
		  break;
		case R:
		  tree->bf = E;
		  *h = -1;
		}
	    }
	}
      else if (sig > 0)
	{
	  tree->right =
	    treeInsAux (tree->right,
			key, value, h, cmp);
	  if (!(*h))
	    {

	      tree->right->super = tree;

	      switch (tree->bf)
		{
		case L:
		  tree->bf = E;
		  *h = -1;
		  break;
		case E:
		  tree->bf = R;
		  break;
		case R:
		  tree = rightBalance (tree);
		  tree->bf = E;
		  *h = -1;
		}
	    }
	}
      return tree;
    }
}

/*INSERE NA ARVORE*/
int
insertAvl (avl tree, void *key, void *value)
{
  int h;

  tree->root =
    treeInsAux (tree->root, key, value,
		&h, tree->keyCmp);

  if (h < 1)
    {
      tree->size++;
      return 0;
    }
  else
    return h;

}

/*BALANCEAMENTO A ESQUERDA PARA A REMOCAO*/
static treenode
rLeftBalance (treenode tree, int *h)
{
  if (tree && tree->left)
    {
      switch (tree->left->bf)
	{
	case L:
	  tree = rightRotate (tree);
	  tree->bf = E;
	  tree->right->bf = E;
	  break;
	case E:
	  tree = rightRotate (tree);
	  tree->bf = R;
	  tree->right->bf = L;
	  *h = 2;
	  break;
	case R:
	  tree->left =
	    leftRotate (tree->left);
	  tree = rightRotate (tree);
	  switch (tree->bf)
	    {
	    case L:
	      tree->left->bf = E;
	      tree->right->bf = E;
	      break;
	    case E:
	      tree->left->bf = E;
	      tree->right->bf = E;
	      break;
	    case R:
	      tree->left->bf = L;
	      tree->right->bf = E;
	    }
	  tree->bf = E;
	}
    }
  return tree;
}

/*BALANCEAMENTO DO LADO DIREITO PARA A REMOCAO*/
static treenode
rRightBalance (treenode tree, int *h)
{
  if (tree && tree->right)
    {
      switch (tree->right->bf)
	{
	case L:
	  tree->right =
	    rightRotate (tree->right);
	  tree = leftRotate (tree);
	  switch (tree->bf)
	    {
	    case L:
	      tree->left->bf = E;
	      tree->right->bf = R;
	      break;
	    case E:
	      tree->left->bf = E;
	      //tree->right->bf=E;
	      break;
	    case R:
	      tree->left->bf = L;
	      tree->right->bf = E;
	    }
	  tree->bf = E;
	  break;
	case E:
	  tree = leftRotate (tree);
	  tree->bf = L;
	  tree->left->bf = R;
	  *h = 2;
	  break;
	case R:
	  tree = leftRotate (tree);
	  tree->bf = E;
	  tree->left->bf = E;
	}
    }
  return tree;
}

/*BUSCAR O DESCENDENTE MAIS A DIREITA. PARA A REMOCAO*/
static treenode
upperLeft (treenode tree)
{
  while (tree->right)
    tree = tree->right;
  return tree;
}


/*
 *REMOCAO AUXILIAR DA ARVORE COM REMOCAO DA 
 * CHAVE E RETORNO DA INFORMACAO
 */
static treenode
treeRemAux (treenode tree, void *key,
	    void **value,
	    void (*del) (void *),
	    int *h, int (*cmp) (void *,
				void *))
{
  int sig;
  treenode aux;

  if (!tree)
    {
      if (value)
	*value = NULL;
      *h = 1;
      return NULL;
    }
  else
    {
      sig = cmp (key, tree->key);

      if (sig < 0)
	{
	  tree->left =
	    treeRemAux (tree->left, key,
			value, del, h, cmp);
	  if (!(*h))
	    {
	      switch (tree->bf)
		{
		case L:
		  tree->bf = E;
		  break;
		case E:
		  tree->bf = R;
		  *h = 2;
		  break;
		case R:
		  tree =
		    rRightBalance (tree, h);
		}
	    }
	  return tree;
	}
      else if (sig > 0)
	{
	  tree->right =
	    treeRemAux (tree->right,
			key, value, del,
			h, cmp);
	  if (!(*h))
	    {
	      switch (tree->bf)
		{
		case L:
		  tree =
		    rLeftBalance (tree, h);
		  break;
		case E:
		  tree->bf = L;
		  *h = 2;
		  break;
		case R:
		  tree->bf = E;
		}
	    }
	  return tree;
	}
      else
	{
	  if (!tree->right)
	    {
	      aux = tree->left;
	      if (aux)
		aux->super = tree->super;
	      if (del)
		del (tree->key);
	      if (value)
		*value = tree->value;

	      free (tree);
	      *h = 0;
	      return aux;
	    }
	  else if (!tree->left)
	    {
	      aux = tree->right;
	      if (aux)
		aux->super = tree->super;
	      if (del)
		del (tree->key);
	      if (value)
		*value = tree->value;
	      free (tree);
	      *h = 0;
	      return aux;
	    }
	  else
	    {
	      if (del)
		del (tree->key);
	      if (value)
		*value = tree->value;
	      aux = upperLeft (tree->left);

	      tree->key = aux->key;
	      tree->value = aux->value;
	      aux->value = NULL;

	      tree->left =
		treeRemAux (tree->left,
			    aux->key,
			    NULL, NULL,
			    h, cmp);

	      if (!(*h))
		{
		  switch (tree->bf)
		    {
		    case L:
		      tree->bf = E;
		      break;
		    case E:
		      tree->bf = R;
		      break;
		    case R:
		      tree =
			rRightBalance
			(tree, h);
		    }
		}
	      return tree;
	    }
	}
    }
}

/*REMOCAO DA AVL*/
int
removeAvl (avl tree, void *key,
	   void **value,
	   void (*del) (void *))
{
  int h;
  tree->root =
    treeRemAux (tree->root, key, value,
		del, &h, tree->keyCmp);

  if (h == 1)			//chave nao existe
    return 1;
  else
    {
      tree->size--;
      return 0;
    }
}

/*DEVOLVE UM ELEMENTO DA AVL*/
int
getAvl (avl tree, void *key, void **value)
{
  treenode aux;
  int r;

  for (r = -1, aux = tree->root;
       aux
       && (r =
	   (*tree->keyCmp) (key,
			    aux->key));
       aux = r < 0 ? aux->left : aux->right);

  if (r)
    {
      *value = NULL;
      return 1;
    }
  else
    {
      *value = aux->value;
      return 0;
    }

}

/*ALTURA DA ARVORE AUXILIAR*/
static unsigned int
hightAvlAux (treenode tree)
{
  unsigned int hLeft, hRight;
  if (!tree)
    return 0;
  else
    {
      hLeft = hightAvlAux (tree->left);
      hRight = hightAvlAux (tree->right);

      return (hLeft >
	      hRight ? ++hLeft : ++hRight);
    }
}

/*ALTURA DA ARVORE*/
unsigned int
hightAvl (avl tree)
{
  if (!tree->size)
    return 0;
  else
    return hightAvlAux (tree->root);
}

/*TAMANHO DA ARVORE - NUMERO DE NODOS*/
unsigned int
sizeAvl (avl tree)
{
  if (tree)
    return tree->size;
  else
    return -1;
}

/*FUNCAO AUXILIAR INORDER*/
static void
inOrderAvlAux (treenode tree,
	       void (*fun) (void *))
{
  if (tree)
    {
      inOrderAvlAux (tree->left, fun);
      fun (tree->value);
      inOrderAvlAux (tree->right, fun);
    }
}

/*TRAVESSIA INORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int
inOrderAvl (avl tree, void (*fun) (void *))
{
  if (tree)
    {
      if (!tree->size)
	return 1;
      else
	{
	  inOrderAvlAux (tree->root, fun);
	  return 0;
	}
    }
  else
    return -1;
}

/*FUNCAO AUXILIAR PREORDER*/
static void
preOrderAvlAux (treenode tree,
		void (*fun) (void *))
{
  if (tree)
    {
      fun (tree->value);
      inOrderAvlAux (tree->left, fun);
      inOrderAvlAux (tree->right, fun);
    }
}

/*TRAVESSIA PREORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int
preOrderAvl (avl tree, void (*fun) (void *))
{
  if (tree)
    {
      if (!tree->size)
	return 1;
      else
	{
	  preOrderAvlAux (tree->root, fun);
	  return 0;
	}
    }
  else
    return -1;
}

/*FUNCAO AUXILIAR POSORDER*/
static void
posOrderAvlAux (treenode tree,
		void (*fun) (void *))
{
  if (tree)
    {
      inOrderAvlAux (tree->left, fun);
      inOrderAvlAux (tree->right, fun);
      fun (tree->value);
    }
}

/*TRAVESSIA POSORDER-SO AFECTA O VALUE E NAO A CHAVE!*/
int
posOrderAvl (avl tree, void (*fun) (void *))
{
  if (tree)
    {
      if (!tree->size)
	return 1;
      else
	{
	  posOrderAvlAux (tree->root, fun);
	  return 0;
	}
    }
  else
    return -1;
}


/*TODAS AS CHAVES DA AVL NUM ITERADOR AUXILIAR*/
static int
avlKeysAux (treenode tree, iterator it)
{
  int r = 0;
  if (tree)
    {
      r = avlKeysAux (tree->left, it);
      r = r || itAdd (it, tree->key);
      r = r || avlKeysAux (tree->right, it);
    }
  return r;
}

/*TODAS AS CHAVES DA AVL NUM ITERADOR-REFERENCIA*/
iterator
avlKeys (avl tree)
{
  if (tree)
    {
      iterator it = itCreate (tree->size);
      if (!it)
	return NULL;
      else if (avlKeysAux (tree->root, it))
	{
	  itDelete (it);
	  return NULL;
	}
      else
	return it;
    }
  else
    return NULL;
}

/*TODAS OS DADOS DA AVL NUM ITERADOR AUXILIAR*/
static int
avlValuesAux (treenode tree, iterator it)
{
  int r = 0;
  if (tree)
    {
      r = avlValuesAux (tree->left, it);
      r = r || itAdd (it, tree->value);
      r = r
	|| avlValuesAux (tree->right, it);
    }
  return r;
}

/*TODAS OS DADOS DA AVL NUM ITERADOR-REFERENCIA*/
iterator
avlValues (avl tree)
{
  if (tree)
    {
      iterator it = itCreate (tree->size);
      if (!it)
	return NULL;
      else if (avlValuesAux (tree->root, it))
	{
	  itDelete (it);
	  return NULL;
	}
      else
	return it;
    }
  else
    return NULL;
}
