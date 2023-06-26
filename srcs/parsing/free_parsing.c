/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:19:42 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/21 23:38:27 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg_in_node(t_cmd_node *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->argument[i])
	{
		free(cmd_node->argument[i]);
		i++;
	}
	free(cmd_node->arg_subst);
	free(cmd_node->argument);
}

void	free_redir_in_node(t_cmd_node *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->redir[i])
	{
		free(cmd_node->redir[i]);
		i++;
	}
	free(cmd_node->redir);
	free(cmd_node->redir_type);
	free(cmd_node->redir_sub);
}

void	free_cmd_node(t_cmd_node *cmd_node)
{
	if (cmd_node->argument != NULL)
		free_arg_in_node(cmd_node);
	if (cmd_node->redir != NULL)
		free_redir_in_node(cmd_node);
}

void	free_cmd_lst(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*tmp;
	int			i;

	i = 0;
	while (*cmd_lst)
	{
		if ((*cmd_lst)->next)
			tmp = (*cmd_lst)->next;
		else
			break ;
		if ((*cmd_lst)->type == CMD_NODE)
		{
			free_cmd_node((*cmd_lst)->cmd_node);
			free((*cmd_lst)->cmd_node);
		}
		free(*cmd_lst);
		i += 1;
		*cmd_lst = tmp;
	}
	if ((*cmd_lst)->type == CMD_NODE)
	{
		i += 1;
		free_cmd_node((*cmd_lst)->cmd_node);
		free((*cmd_lst)->cmd_node);
	}
}
