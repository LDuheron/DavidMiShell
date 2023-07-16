/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:39 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/16 14:21:10 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = data->cmd_lst;
	while (g_status < 2 && cmd_lst)
	{
		if (cmd_lst->type == CMD_NODE && set_redirection(data, cmd_lst))
		{
			ft_launch_cmd(data, cmd_lst);
		}
		cmd_lst = cmd_lst->next;
	}
	if (g_status > 0)
		g_status = 0;
	ft_wait(data);
	signal(SIGINT, &sigint_handler);
}

/* This check handles the case if the **argumen in NULL and
there is something in **redir */
void	print_error_cmd(t_data *data, t_cmd_lst *cmd_lst)
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
	data->exit_code = errno;
	exit(data->exit_code);
}

void	print_error_dir(t_data *data, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->cmd_node->redir[i])
	{
		if (!access(cmd_lst->cmd_node->redir[i], X_OK))
		{
			ft_putstr_fd("DavidMishell: ", 2);
			ft_putstr_fd(cmd_lst->cmd_node->redir[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			break ;
		}
		i++;
	}
	data->exit_code = errno;
	exit(data->exit_code);
}

char	*absolute_path_to_cmd(char *cmd, char **path_dirs)
{
	char	*to_execute;
	int		i;

	if (!path_dirs)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (path_dirs && path_dirs[i])
	{
		to_execute = ft_strjoin(ft_strjoin(path_dirs[i], "/"), cmd);
		if (access(to_execute, X_OK) == 0)
			break ;
		free(to_execute);
		to_execute = NULL;
		i++;
	}
	free_tab(path_dirs);
	if (!to_execute)
		return (cmd);
	return (to_execute);
}

void	ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	char	**arg;
	char	*to_execute;

	data->path_dirs = get_path_directories(data->m_envp);
	if (cmd_lst->cmd_node->argument)
	{
		arg = cmd_lst->cmd_node->argument;
		expand_envp(data, cmd_lst->cmd_node);
		to_execute = absolute_path_to_cmd(arg[0], data->path_dirs);
		data->exit_code = execve(to_execute, cmd_lst->cmd_node->argument,
				data->m_envp);
		print_error_cmd(data, cmd_lst);
	}
	else if (cmd_lst->cmd_node->redir)
	{
		print_error_dir(data, cmd_lst);
	}
}
