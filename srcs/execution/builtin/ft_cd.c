/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:34:30 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/22 14:17:54 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(char **m_envp, const char *name)
{
	int	i;
	int	len;

	if (!m_envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(m_envp[i], name, len) == 0 && m_envp[i][len] == '=')
			return (m_envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*ft_copy_env_value(char **m_envp, const char *name, char *path)
{
	int	i;
	int	len;

	if (!m_envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(m_envp[i], name, len) == 0 && m_envp[i][len] == '=')
			return (ft_strcpy(path, m_envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

static void	change_pwd(char **m_envp, char *key)
{	
	char	*get_cwd;
	int		i;

	i = -1;
	while (m_envp[++i])
		if (ft_strncmp(m_envp[i], key, ft_strlen(key)) == 0)
			break ;
	if (ft_strcmp(key, "OLDPWD=") == 0)
	{
		get_cwd = ft_getenv(m_envp, "PWD");
		if (m_envp[i])
			free(m_envp[i]);
		m_envp[i] = ft_strjoin(key, get_cwd);
	}
	else
	{
		get_cwd = getcwd(NULL, 0);
		if (m_envp[i])
			free(m_envp[i]);
		m_envp[i] = ft_strjoin(key, get_cwd);
		free(get_cwd);
	}
}

static void	ft_update_pwds(t_data *data, char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		data->exit_code = 1;
	}
	if (data->exit_code != 1)
	{
		data->exit_code = 0;
		change_pwd(data->m_envp, "OLDPWD=");
		change_pwd(data->m_envp, "PWD=");
	}
}

void	ft_cd(t_data *data, t_cmd_lst *cmd_lst)
{
	char	path[BUFFER];

	ft_bzero(path, BUFFER);
	if (too_many_arguments(data, cmd_lst))
		return ;
	if (settings_cd(cmd_lst) == 0)
		ft_copy_env_value(data->m_envp, "HOME", path);
	else if (ft_strcmp(cmd_lst->cmd_node->argument[1], "-") == 0)
	{
		ft_copy_env_value(data->m_envp, "OLDPWD", path);
		ft_putendl_fd(path, 1);
	}
	else if (cmd_lst->cmd_node->argument[1][0] == '~'
		&& cmd_lst->cmd_node->argument[1][1] == '/')
	{
		ft_copy_env_value(data->m_envp, "HOME", path);
		ft_strcat(path, cmd_lst->cmd_node->argument[1] + 1);
	}
	else
		ft_strcpy(path, cmd_lst->cmd_node->argument[1]);
	ft_update_pwds(data, path);
}
