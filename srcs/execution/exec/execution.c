/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:07:17 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/10 15:53:28by sbocanci         ###   ########.fr       */
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
	char	**argument;
	int	builtin;
	
	argument = cmd_lst->cmd_node->argument;
	builtin = N_A;
	if (argument)
	{
		if (ft_strncmp(argument[0], "cd", 2) == 0)
			builtin = CD;
		else if (ft_strncmp(argument[0], "echo", 4) == 0)
			builtin = ECHO;
		else if (ft_strncmp(argument[0], "env", 3) == 0)
			builtin = ENV;
		else if (ft_strncmp(argument[0], "exit", 4) == 0)
			builtin = EXIT;
		else if (ft_strncmp(argument[0], "export", 6) == 0)
			builtin = EXPORT;
		else if (ft_strncmp(argument[0], "pwd", 3) == 0)
			builtin = PWD;
		else if (ft_strncmp(argument[0], "unset", 5) == 0)
			builtin = UNSET;
	}
	return (builtin);
}

void	exec_builtin(t_data *data, t_cmd_lst *cmd_lst, int builtin)
{
	/* DEBUG */
	//printf("\t\t..exec_builtin.. ..expand here..\n\n");
	//print_cmd_lst(&cmd_lst);
	/* ***** */
	expand_envp(cmd_lst->cmd_node, data->m_envp);

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
	
	/* DEBUG 
	printf("\t");
	printf("..execution..\n");
	*/
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

/* This check handles the case if the **argumen in NULL and there is somethingin **redir */
void	print_error(t_data *data, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument)
	{
		if (ft_strchr_i(cmd_lst->cmd_node->argument[0], '/') == -1)
		{
			ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
		{
			ft_putstr_fd("DavidMishell: ", 2);
			ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	else  if (cmd_lst->cmd_node->redir)
	{
		ft_putstr_fd("DavidMishell: ", 2);
		ft_putstr_fd(cmd_lst->cmd_node->redir[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->exit_return = errno;
	exit(data->exit_return);
}

char	*absolute_path_to_cmd(char *cmd, char **path_dirs)
{
	char	*to_execute;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (path_dirs[i])
	{
		to_execute = ft_strjoin(ft_strjoin(path_dirs[i], "/"), cmd);
		printf("\tpaths[%d]: [%s], to_exec: [%s]\n",i,	path_dirs[i], to_execute);

		if (access(to_execute, X_OK) == 0)
			break ;
		free(to_execute);
		to_execute = NULL;
		i++;
	}
	if (!to_execute)
		return (cmd);
	return (to_execute);
}

void ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	char	**arg;
	char	*to_execute;

	if (cmd_lst->cmd_node->argument)
	{
		arg = cmd_lst->cmd_node->argument;
		expand_envp(cmd_lst->cmd_node, data->m_envp);
		to_execute = absolute_path_to_cmd(arg[0], data->path_dirs);
		data->exit_return = execve(to_execute, cmd_lst->cmd_node->argument, data->env);
		print_error(data, cmd_lst);
	}
	else
		print_error(data, cmd_lst);
}

/*
void ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	int		y;
	char	*exec;

	expand_envp(cmd_lst->cmd_node, data->m_envp);

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
*/
