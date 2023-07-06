/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:31:11 by svoi              #+#    #+#             */
/*   Updated: 2023/07/06 19:34:47 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Need to take care of ft_exit */
void ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	(void)data;
	(void)cmd_lst;
}

/*
void ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1])
	{
	}

	rl_clear_history();
	// free all memory here
    exit(data->exit_return);
}
*/
