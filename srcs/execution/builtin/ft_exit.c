/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:31:11 by svoi              #+#    #+#             */
/*   Updated: 2023/07/05 23:42:47 by svoi             ###   ########.fr       */
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
{
	if (!cmd_lst->cmd_node->redir)
    {
        if (cmd_lst->cmd_node->argument[1] != NULL)
            data->exit_return = ft_atoi_exit(cmd_lst->cmd_node->argument[1]);
        else
            data->exit_return = 0;
    }
	//ft_putstr_fd("exit\n", 1);
    //cmd_lst->builtin = EXIT;
    exit(data->exit_return);
}
*/
