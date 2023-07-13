/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:39 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/13 15:51:17 by sbocanci         ###   ########.fr       */
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
		return ("CMD_NODE");
	if (type == PIPE_NODE)
		return ("PIPE_NODE");
	return ("no_type");
}
/* ***** */

void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*tmp;

	/* DEBUG */
	//printf("\t..START..exetition..\tg_status: [%d], exit_code: [%d]\n", g_status, data->exit_code);
	/* ***** */
	cmd_lst = data->cmd_lst;
	tmp = cmd_lst;
	while (tmp)
	{
		if (tmp->type == CMD_NODE && cmd_lst->cmd_node->redir)
		{
			set_redirection(data, tmp);
		}
		tmp = tmp->next;
	}
	/* DEBUG */
	//printf("\t..BEFORE..execution..\tg_status: [%d], exit_code: [%d]\n", g_status, data->exit_code);
	/* ***** */
	while (g_status < 2 && cmd_lst)
	{
		if (cmd_lst->type == CMD_NODE)
		{
			ft_launch_cmd(data, cmd_lst);
		}
		cmd_lst = cmd_lst->next;
	}
	if (g_status > 0)
		g_status = 0;

	/* DEBUG */
	//printf("\t..AFTER..execution..\tg_status: [%d], exit_code: [%d]\n", g_status, data->exit_code);
	/* ***** */
	ft_wait(data);
}

/* This check handles the case if the **argumen in NULL and
there is something in **redir */

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
	else if (cmd_lst->cmd_node->redir)
	{
		ft_putstr_fd("DavidMishell: ", 2);
		ft_putstr_fd(cmd_lst->cmd_node->redir[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->exit_code = errno;
	exit(data->exit_code);
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

void	ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	char	**arg;
	char	*to_execute;

	if (cmd_lst->cmd_node->argument)
	{
		arg = cmd_lst->cmd_node->argument;
		expand_envp(data, cmd_lst->cmd_node);
		to_execute = absolute_path_to_cmd(arg[0], data->path_dirs);
		data->exit_code = execve(to_execute, cmd_lst->cmd_node->argument,
				data->m_envp);
		print_error(data, cmd_lst);
	}
	else
		print_error(data, cmd_lst);
}
