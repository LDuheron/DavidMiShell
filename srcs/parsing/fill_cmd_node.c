/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:24:21 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 18:18:10 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FILL_ARG :

int	fill_arg(t_cmd_node *cmd_node, t_tokens **token, int i)
{
	int	nb_subst;
	int	j;

	j = 0;
	nb_subst = nb_dollar((*token)->content);
	cmd_node->argument[i] = ft_strdup((*token)->content);
	cmd_node->arg_subst[i] = malloc(sizeof (int) * (nb_subst + 1));
	if (!cmd_node->arg_subst[i])
		return (ERROR_MALLOC);
	cmd_node->arg_subst[i][nb_subst] = -2;
	while (j < nb_subst)
	{
		cmd_node->arg_subst[i][j] = -2;
		cmd_node->arg_subst[i][j] = (*token)->dollars_tab[j];
		j++;
	}
	return (SUCCESS);
}

int	fill_redirection(t_cmd_node *cmd_node, t_tokens **token, int i)
{
	int	nb_subst;
	int	j;

	j = 0;
	nb_subst = nb_dollar((*token)->content);
	cmd_node->redir[i] = ft_strdup((*token)->content);
	cmd_node->redir_type[i] = (*token)->type;
	cmd_node->redir_sub[i] = malloc(sizeof (int) * (nb_subst + 1));
	if (!cmd_node->redir_sub[i])
		return (ERROR_MALLOC);
	cmd_node->redir_sub[i][nb_subst] = -2;
	while (j < nb_subst)
	{
		cmd_node->redir_sub[i][j] = -2;
		cmd_node->redir_sub[i][j] = (*token)->dollars_tab[j];
		j++;
	}
	return (SUCCESS);
}

void	set_last_c_null(t_cmd_node *cmd_node, int i_arg, int i_redir)
{
	if (cmd_node->argument != NULL)
	{
		cmd_node->argument[i_arg] = NULL;
		cmd_node->arg_subst[i_arg] = 0;
	}
	if (cmd_node->redir != NULL)
	{
		cmd_node->redir[i_redir] = NULL;
		cmd_node->redir_type[i_redir] = 0;
		cmd_node->redir_sub[i_redir] = 0;
	}
}

int	fill_cmd_node(t_tokens **token, t_cmd_node *cmd_node)
{
	int	i_arg;
	int	i_redir;
	int	flag;

	i_arg = 0;
	i_redir = 0;
	flag = SUCCESS;
	while (*token && (*token)->type != PIPE && flag == SUCCESS)
	{
		if ((*token)->type == WORD)
		{
			flag = fill_arg(cmd_node, token, i_arg);
			i_arg++;
		}
		else
		{
			flag = fill_redirection(cmd_node, token, i_redir);
			i_redir++;
		}
		eat_token(token);
	}
	set_last_c_null(cmd_node, i_arg, i_redir);
	return (flag);
}
