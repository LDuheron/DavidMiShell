/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:19:42 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/18 18:15:46 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_int_tab(int **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab[i])
	{
		free(tab[i]);
		tab = NULL;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	node_destroy(t_cmd_lst *list)
{
	if (list->cmd_node)
	{
		if (list->cmd_node->argument)
			free_char_tab(list->cmd_node->argument);
		if (list->cmd_node->redir)
		{
			free_char_tab(list->cmd_node->redir);
		}
		if (list->cmd_node->arg_subst)
			free_int_tab(list->cmd_node->arg_subst);
		if (list->cmd_node->redir_sub)
			free_int_tab(list->cmd_node->redir_sub);
		if (list->cmd_node->redir_type)
			free(list->cmd_node->redir_type);
	}
	if (list->cmd_node)
		free(list->cmd_node);
}

void	list_destroy(t_cmd_lst *list)
{
	if (!list || !(list))
		return ;
	list_destroy((list)->next);
	node_destroy(((list)));
	free(list);
	list = NULL;
}
