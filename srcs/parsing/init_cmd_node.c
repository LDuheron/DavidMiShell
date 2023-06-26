/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:32:36 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/21 22:21:22 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd_node_to_null(t_cmd_node *cmd_node)
{
	cmd_node->argument = NULL;
	cmd_node->arg_subst = NULL;
	cmd_node->redir = NULL;
	cmd_node->redir_type = NULL;
	cmd_node->redir_sub = NULL;
}

int	init_arg_tab(t_cmd_lst *cmd_lst, int i_arg)
{
	if (i_arg != 0)
	{
		cmd_lst->cmd_node->argument = malloc(sizeof (char *) * (i_arg + 1));
		if (cmd_lst->cmd_node->argument == NULL)
			return (ERROR_MALLOC);
		cmd_lst->cmd_node->arg_subst = malloc(sizeof (int *) * (i_arg + 1));
		if (cmd_lst->cmd_node->arg_subst == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	init_redir_tab(t_cmd_lst *cmd_lst, int i_redir)
{
	if (i_redir != 0)
	{
		cmd_lst->cmd_node->redir = malloc(sizeof (char *) * (i_redir + 1));
		if (cmd_lst->cmd_node->redir == NULL)
			return (ERROR_MALLOC);
		cmd_lst->cmd_node->redir_type = malloc(sizeof (int) * (i_redir + 1));
		if (cmd_lst->cmd_node->redir_type == NULL)
			return (ERROR_MALLOC);
		cmd_lst->cmd_node->redir_sub = malloc(sizeof (int *) * (i_redir + 1));
		if (cmd_lst->cmd_node->redir_sub == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	init_cmd_node(t_tokens **token, t_cmd_lst *cmd_lst)
{
	t_tokens		*tmp;
	int				i_arg;
	int				i_redir;
	int				flag;

	flag = SUCCESS;
	i_arg = 0;
	i_redir = 0;
	cmd_lst->cmd_node = malloc(sizeof(t_cmd_node));
	if (!(cmd_lst->cmd_node))
		return (ERROR_MALLOC);
	set_cmd_node_to_null(cmd_lst->cmd_node);
	tmp = *token;
	while (tmp && (*tmp).type != PIPE)
	{
		if ((*tmp).type == WORD)
			i_arg++;
		else
			i_redir++;
		tmp = tmp->next;
	}
	flag = init_arg_tab(cmd_lst, i_arg);
	flag = init_redir_tab(cmd_lst, i_redir);
	return (flag);
}
