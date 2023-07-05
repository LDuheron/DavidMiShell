/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:07:17 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/05 13:26:38 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ft_exec(t_data *data)
{
	t_cmd_lst	*cmd;
	int			fd[2];

	//cmd = data->cmdIndex->begin;
	while (cmd)
	{
		//printf("\tnb_pipes: '%d'\n", data->cmdIndex->nb_pipe);
		if (cmd->spec_built)
			spec_built(cmd, data);
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
		}
		cmd = cmd->next;
	}
	wait_all_and_finish(data, data->cmdIndex->begin);
	return (1);
}
*/

int	check_builtin(t_cmd_lst *cmd_lst)
{
	int	builtin;

	builtin = N_A;
	if (ft_strncmp(cmd_lst->cmd_node->argument[0], "cd", 2) == 0)
		builtin = CD;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "exit", 4) == 0)
		builtin = EXIT;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "export", 6) == 0)
		builtin = EXPORT;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "unset", 5) == 0)
		builtin = UNSET;
	return (builtin);
}

void	exec_builtin(t_data *data, t_cmd_lst *cmd_lst, int builtin)
{
	if (builtin == CD)
		ft_cd(data, cmd_lst);
	else if (builtin == ECHO)
		ft_echo(data, cmd_lst);
	else if (builtin == ENV)
		ft_env(data, cmd_lst);
	else if (builtin == EXIT)
		ft_exit(data, cmd_lst);
	else if (builtin == EXPORT)
		ft_export(data, cmd_lst);
	else if (builtin == PWD)
		ft_pwd(data, cmd_lst);
	else if (builtin == UNSET)
		ft_unset(data, cmd_lst);
}

void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;
	int			fd[2];
	int			builtin;
	
	//check_builtin_first(data);
	builtin = 0;
	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		builtin = check_builtin(cmd_lst);

		//printf("\tnb_pipes: '%d'\n", data->cmdIndex->nb_pipe);

		if (builtin)
			exec_builtin(data, cmd_lst, builtin);
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
		}
		cmd = cmd->next;
	}
	wait_all_and_finish(data, data->cmdIndex->begin);
}
