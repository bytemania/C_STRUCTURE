#include<stdlib.h>
#include<stdio.h>
#include"iterator.h"

/*CRIA UM NOVO ITERADOR*/
iterator
itCreate (const unsigned int size)
{
  unsigned int i;
  iterator it =
    (iterator) malloc (sizeof (Iterator));

  if (!it)
    {
      return NULL;
    }
  else
    {
      it->capacity = size;
      it->size = 0;
      it->pos = 0;
      it->values =
	(void **) calloc (size,
			  sizeof (void *));

      if (!it->values)
	{
	  free (it);
	  return NULL;
	}

      for (i = 0; i < size; i++)
	it->values[i] = NULL;
      return it;
    }

}

/*ELIMINA UM ITERADOR*/
void
itDelete (iterator it)
{
  free (it->values);
  free (it);
}

/*ADICIONA UM ELEMENTO AO ITERADOR*/
int
itAdd (iterator it, void const *val)
{
  if (it->size == it->capacity)
    return 1;
  else
    {
      it->values[it->size] = (void *) val;
      it->size++;
      return 0;
    }
}

/*DEVOLVE O PROXIMO ELEMENTO DE UM ITERADOR*/
int
itNext (iterator it, void **val)
{
  if (it->pos >= it->size)
    {
      *val = NULL;
      return 1;
    }
  else
    {
      *val = it->values[it->pos];
      it->pos++;
      return 0;
    }
}

/*VERIFICA SE EXISTE PROXIMO ELEMENTO DE UM VECTOR*/
int
itHasNext (const iterator it)
{
  return (it->pos < it->size);
}

/*DEVOLVE O ELEMENTO ANTERIOR DE UM ITERADOR*/
int
itPrev (iterator it, void **val)
{
  if (!it->pos)
    {
      *val = NULL;
      return 1;
    }
  else
    {
      it->pos--;
      *val = it->values[it->pos];
      return 0;
    }
}

/*DEVOLVE SE EXISTE O ELEMENTO ANTERIOR NUM ITERADOR*/
int
itHasPrev (iterator it)
{
  return it->pos;
}

/* 
 * VERIFICA QUAL O ELEMENTO NUMA DETERMINADA
 * POSICAO DO ITERADOR
 */
int
itAt (iterator it,
      const unsigned int index, void **val)
{
  if (index >= it->size)
    {
      *val = NULL;
      return 1;
    }
  else
    {
      *val = it->values[index];
      return 0;
    }
}

/*ALTERA A POSICAO ACTUAL DO ITERADOR*/
int
itSetPos (iterator it, const unsigned int n)
{
  if (n >= it->size)
    return 1;
  else
    {
      it->pos = n;
      return 0;
    }
}

/*DETERMINA A POSICAO ACTUAL DO ITERADOR*/
unsigned int
itGetPos (const iterator it)
{
  return it->pos;
}
