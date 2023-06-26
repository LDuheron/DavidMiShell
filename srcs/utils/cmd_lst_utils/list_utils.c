/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:00 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/23 16:16:12 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_tokens	*ft_lstnew(char *content)
{
	t_tokens	*new_elem;

	new_elem = malloc (sizeof(t_tokens));
	if (!new_elem)
		return (NULL);
	new_elem->type = 0;
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
