/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:20:39 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/17 11:42:45 sbocanci         ###   ########.fr       */
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
    char	to_execute[BUFFER];
    int		i;

    if (path_dirs == NULL || (access(cmd, X_OK) == 0))
        return (ft_strdup(cmd));
    i = 0;
    while (path_dirs && path_dirs[i])
    {
        ft_strcpy(to_execute, path_dirs[i]);
        ft_strcat(to_execute, "/");
        ft_strcat(to_execute, cmd);
        if (access(to_execute, X_OK) == 0)
            break ;
        i++;
    }
    free_tab(path_dirs);
    if (to_execute[0] == '\0')
        return (ft_strdup(cmd));
    return (ft_strdup(to_execute));
}

void	ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
    char	**arg;
	char	*dup;
    char	to_execute[BUFFER];

    data->path_dirs = get_path_directories(data->m_envp);
    if (cmd_lst->cmd_node->argument)
    {
        arg = cmd_lst->cmd_node->argument;
        expand_envp(data, cmd_lst->cmd_node);
		dup = absolute_path_to_cmd(arg[0], data->path_dirs);
        ft_strcpy(to_execute, dup);
		free(dup);
        data->exit_code = execve(to_execute, cmd_lst->cmd_node->argument, data->m_envp);
        print_error_cmd(data, cmd_lst);
    }
    else if (cmd_lst->cmd_node->redir)
    {
        print_error_dir(data, cmd_lst);
    }
}
