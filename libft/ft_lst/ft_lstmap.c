/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:37:55 by vinni             #+#    #+#             */
/*   Updated: 2023/04/09 14:44:49 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_lst/ft_lst.h"

static void	*ft_clear(void *i, t_list *new, void del(void *))
{
	(del)(i);
	ft_lstclear(&new, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*i;

	i = 0;
	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		i = f(lst->content);
		if (!i)
			return (ft_clear(i, new, del));
		tmp = ft_lstnew(i);
		if (!tmp)
		{
			return (ft_clear(i, new, del));
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
/*
int main()
{
	t_list *lst;
	t_list *new;
	t_list *tmp;
	int i;

	i = 0;
	lst = NULL;
	while (i < 5)
	{
		tmp = ft_lstnew(&i);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	new = ft_lstmap(lst, &ft_lstnew, &ft_lstclear);
	while (new)
	{
		printf("%d", *(int *)new->content);
		new = new->next;
	}
	return (0);
}
*/

/*La función ft_ stamp recibe tres argumentos:
lst, un puntero a una estructura de tipo t_list,
f, un puntero a una función que recibe un puntero
a void y devuelve un puntero a void, y del, un
puntero a una función que recibe un puntero a void
y no devuelve nada.La función comienza verificando
que lst y f no sean nulos (if (!lst || !f) return (NULL)).
Si alguno de ellos es nulo, la función devuelve NULL.
Luego, se declara una estructura lista llamada new
inicializada en NULL. Luego, se tira sobre lst hasta
que este sea nulo. En cada iteración, se invoca la función
f con el contenido de lst (f(lst->content)) y se pasa
el resultado a la función ft_lstnew, que devuelve una
nueva estructura t_list. Esta estructura se almacena en
una variable temporal llamada tmp. Si tmp es nulo, se
invoca la función ft_ stclair con la dirección de new y
del, y la función devuelve NULL. Si tmp no es nulo, se
invoca la función ft_lstadd_back con la dirección de new
y tmp para agregar la nueva estructura a la lista new.
Después de la iteración, se asigna a lst su siguiente 
elemento (lst = lst->next). Finalmente, al finalizar
la iteración, la función devuelve new.
En resumen, ft_ stamp crea una nueva lista, aplicando
una función dada a cada elemento de una lista dada
y devuelve la nueva lista.*/
