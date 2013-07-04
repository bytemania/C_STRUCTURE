#ifndef _ITERATOR_
#define _ITERATOR_

/*ESTRUTURA DE DADOS*/

typedef struct _iterator_
{
  unsigned int capacity;
  unsigned int size;
  unsigned int pos;
  void **values;
} *iterator, Iterator;

 /*FUNCOES*/
/*CRIA UM NOVO ITERADOR*/
  iterator itCreate (const unsigned int
		     size);

/*ELIMINA UM ITERADOR*/
void itDelete (iterator it);

/*ADICIONA UM ELEMENTO AO ITERADOR*/
int itAdd (iterator it, void const *val);

/*DEVOLVE O PROXIMO ELEMENTO DE UM ITERADOR*/
int itNext (iterator it, void **val);

/*VERIFICA SE EXISTE PROXIMO ELEMENTO DE UM VECTOR*/
int itHasNext (const iterator it);

/*DEVOLVE O ELEMENTO ANTERIOR DE UM ITERADOR*/
int itPrev (iterator it, void **val);

/*DEVOLVE SE EXISTE O ELEMENTO ANTERIOR NUM ITERADOR*/
int itHasPrev (iterator it);

/*
 * VERIFICA QUAL O ELEMENTO NUMA DETERMINADA POSICAO 
 * DO ITERADOR
 */
int itAt (iterator it,
	  const unsigned int index,
	  void **val);

/*ALTERA A POSICAO ACTUAL DO ITERADOR*/
int itSetPos (iterator it,
	      const unsigned int n);

/*DETERMINA A POSICAO ACTUAL DO ITERADOR*/
unsigned int itGetPos (const iterator it);

#endif
