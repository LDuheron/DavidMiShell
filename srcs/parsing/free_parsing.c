/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:19:42 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/29 19:17:55 by lduheron         ###   ########.fr       */
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
		free(cmd_node->arg_subst[i]);
		i++;
	}
	free(cmd_node->argument);
	free(cmd_node->arg_subst);
}

void	free_redir_in_node(t_cmd_node *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->redir[i])
	{
		free(cmd_node->redir[i]);
		free(cmd_node->redir_sub[i]);
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
			free(*cmd_lst);
		}
		else
			free(*cmd_lst);
		*cmd_lst = tmp;
	}
	if ((*cmd_lst)->type == CMD_NODE)
	{
		free_cmd_node((*cmd_lst)->cmd_node);
		free((*cmd_lst)->cmd_node);
		free(*cmd_lst);
	}
	else
		free(cmd_lst);
	if (cmd_lst)
		printf("remains\n\n\n\n\n");
	else
		free(cmd_lst);
}


// void	free_cmd_lst(t_cmd_lst **cmd_lst)
// {
// 	t_cmd_lst	*tmp;
// 	int			i;

// 	tmp = NULL;
// 	tmp = *cmd_lst;
// 	i = 0;
// 	while (cmd_lst)
// 	{
// 		if ((*cmd_lst)->type == CMD_NODE)
// 		{
// 			tmp = *cmd_lst;
// 			free_cmd_node(tmp->cmd_node);
// 			cmd_lst = &(*cmd_lst)->next;
// 		}
// 		else
// 		{
// 			tmp = *cmd_lst;
// 			cmd_lst = &(*cmd_lst)->next;
// 			free(cmd_lst);
// 		}
// 		if (!tmp->next)
// 			break ;
// 		i++;
// 	}
// }
