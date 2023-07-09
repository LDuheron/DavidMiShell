/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:07:17 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/10 00:15:01 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* DEBUG */
char	*print_builtin(int builtin)
{
	if (builtin == CD)	
		return ("CD");
	else if (builtin == ECHO)	
		return ("ECHO");
	else if (builtin == ENV)	
		return ("ENV");
	else if (builtin == EXIT)	
		return ("EXIT");
	else if (builtin == EXPORT)	
		return ("EXPORT");
	else if (builtin == PWD)	
		return ("PWD");
	else if (builtin == UNSET)	
		return ("UNSET");
	else
		return ("N_DEF");
}

char	*print_node_type(int type)
{
	if (type == CMD_NODE)
		return("CMD_NODE");
	if (type == PIPE_NODE)
		return("PIPE_NODE");
	return ("no_type");
}
/* ***** */

int	check_builtin(t_cmd_lst *cmd_lst)
{
	int	builtin;

	builtin = N_A;
	if (ft_strncmp(cmd_lst->cmd_node->argument[0], "cd", 2) == 0)
		builtin = CD;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "echo", 4) == 0)
		builtin = ECHO;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "env", 3) == 0)
		builtin = ENV;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "exit", 4) == 0)
		builtin = EXIT;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "export", 6) == 0)
		builtin = EXPORT;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "pwd", 3) == 0)
		builtin = PWD;
	else if (ft_strncmp(cmd_lst->cmd_node->argument[0], "unset", 5) == 0)
		builtin = UNSET;
	return (builtin);
}

void	exec_builtin(t_data *data, t_cmd_lst *cmd_lst, int builtin)
{
	/* DEBUG */
	printf("\t\t..exec_builtin.. ..expand here..\n\n");
	
	expand_envp(cmd_lst->cmd_node, data->m_envp);
	//print_cmd_lst(&cmd_lst);
	/* ***** */

	if (builtin == CD)
		ft_cd(data, cmd_lst);
	else if (builtin == ECHO)
		ft_echo(data, cmd_lst);
	else if (builtin == ENV)
		ft_env(data);
	else if (builtin == EXIT)
		ft_exit(data, cmd_lst);
	else if (builtin == EXPORT)
		ft_export(data, cmd_lst);
	else if (builtin == PWD)
		ft_pwd(data);
	else if (builtin == UNSET)
		ft_unset(data, cmd_lst);
}

void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;
	
	/* DEBUG */
	printf("\t");
	printf("..execution..\n");
	/* ***** */

	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		if (cmd_lst->type == CMD_NODE)
		{
			ft_launch_cmd(data, cmd_lst);
		}
		cmd_lst = cmd_lst->next;
	}
	ft_wait(data);
}

void ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	int		y;
	char	*exec;

	/* DEBUG */
	printf("\t\t..ft_execve.. ..expand here..\n\n");

	expand_envp(cmd_lst->cmd_node, data->m_envp);
	/* ***** */

	y = 0;
	while (data->path_dirs[++y])
	{
		exec = ft_strjoin(ft_strjoin(data->path_dirs[y], "/"), cmd_lst->cmd_node->argument[0]);
		//printf("execve, path'%s', pid:'%d'\n", exec, data.pid);
		data->exit_return = execve(exec, cmd_lst->cmd_node->argument, data->env);
		//printf("exit_return: '%d'\n", data->exit_return);
		free(exec);
	}
	ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_return = errno;
	exit(data->exit_return);
}
/*
*/
