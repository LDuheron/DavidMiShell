/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:36:53 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 15:11:58 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_cmd_lst **cmd_lst, t_tokens **token)
{
	t_cmd_lst	*tmp;
	int			flag;

	tmp = malloc(sizeof(t_cmd_lst));
	if (!tmp)
		return (ERROR_MALLOC);
	tmp->type = CMD_NODE;
	tmp->next = NULL;
	tmp->cmd_node = NULL;
	flag = init_cmd_node(token, tmp);
	if (flag != SUCCESS)
		return (flag);
	flag = fill_cmd_node(token, tmp->cmd_node);
	if (flag != SUCCESS)
		return (flag);
	ft_lstadd_back_cmd_lst_node(cmd_lst, tmp);
	return (SUCCESS);
}

int	parse_pipe(t_cmd_lst **cmd_lst, t_tokens **token)
{
	t_cmd_lst	*tmp;

	tmp = malloc(sizeof(t_cmd_lst));
	if (!tmp)
		return (ERROR_MALLOC);
	tmp->type = PIPE_NODE;
	tmp->cmd_node = NULL;
	tmp->next = NULL;
	eat_token(token);
	ft_lstadd_back_cmd_lst_node(cmd_lst, tmp);
	return (SUCCESS);
}

int	parsing(t_cmd_lst **cmd_lst, t_tokens **token)
{
	int	flag;

	flag = SUCCESS;
	while (*token != NULL)
	{
		if ((*token)->type != PIPE)
			flag = parse_command(cmd_lst, token);
		else
			flag = parse_pipe(cmd_lst, token);
		if (flag != SUCCESS)
			return (flag);
	}
	return (flag);
}
