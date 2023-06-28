/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:01:16 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/27 19:15:26 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_cmd_node(t_cmd_node *cmd_node)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	j = 0;
// 	if (cmd_node == NULL)
// 	{
// 		printf("Error: cmd_node is NULL\n");
// 		return ;
// 	}
// 	if (cmd_node->argument)
// 	{
// 		while (cmd_node->arg_subst[0][j] != -2)
// 		{
// 			free(cmd_node->arg_subst[0][j]);
// 			j++;
// 		}
// 	}
// 	if (cmd_node->argument != NULL)
// 	{
// 		while (cmd_node->argument[i])
// 		{
// 			j = 0;
// 			while (cmd_node->arg_subst[i][j] != -2)
// 			{
// 					free(cmd_node->arg_subst[i][j]);
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// 	i = 0;
// 	if (cmd_node->redir != NULL)
// 	{
// 		while (cmd_node->redir[i])
// 		{
// 			j = 0;
// 			free(cmd_node->redir_sub[i][j]);
// 			while (cmd_node->redir_sub[i][j] != -2)
// 			{
// 					free(cmd_node->redir_type[i]);
// 				j++;
// 			}
// 			free(cmd_node->redir[i]);
// 			i++;
// 		}
// 	}
// }

// // void	free_ecmd_lst(t_cmd_lst **cmd_lst)
// {
// 	t_cmd_lst	*tmp;
// 	int			i;

// 	tmp = *cmd_lst;
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD_NODE)
// 			free_cmd_node(tmp->cmd_node);
// 		if (!tmp->next)
// 			break ;
// 		i++;
// 		tmp = tmp->next;
// 	}
// }