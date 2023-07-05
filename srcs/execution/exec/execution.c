/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:07:17 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/05 23:59:22 by svoi             ###   ########.fr       */
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
/* ***** */

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

/* Need to take care of ft_pipe() as separate f().. */
void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;
	//int			fd[2];
	int			builtin;
	
	builtin = 0;
	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		builtin = check_builtin(cmd_lst);

		//printf("\tbuiltin: '%d'\n", print_builtin(builtin));

		if (builtin)
			exec_builtin(data, cmd_lst, builtin);
		else
		{
			/*
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
			*/
		}
		cmd_lst = cmd_lst->next;
	}
	ft_wait(data);
}

/* Need to take care of path_directories().. */
void ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	(void)data;
	(void)cmd_lst;
}
/*
{
	int y;
	char *exec;

	//no_str(cmd->cmd);
	y = 0;
	while (data->path_dirs[++y])
	{
		exec = ft_strjoin(ft_strjoin(data->path_dirs[y], "/"), cmd_lst->cmd_node->argument[0]);
		//printf("execve, path'%s', pid:'%d'\n", exec, global.pid);
		data->exit_return = execve(exec, cmd_lst->cmd_node->argument, data->env);
		//printf("exit_return: '%d'\n", data->exit_return);
		free(exec);
	}
	ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_return = errno;
	exit(data->exit_return);
}
*/
