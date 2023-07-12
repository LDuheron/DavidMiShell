/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:30:20 by svoi              #+#    #+#             */
/*   Updated: 2023/07/12 18:07:11 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char **m_envp, char *key)
{	
	char	*get_cwd;
	int		i;

	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(m_envp[i], key, ft_strlen(key)) == 0)
			break ;
		i++;
	}
	get_cwd = getcwd(NULL, 0);
	if (m_envp[i])
		free(m_envp[i]);
	m_envp[i] = ft_strjoin(key, get_cwd);
	free(get_cwd);
}

/* this adds new key=value pair to the data->m_envp. 
** also appends VALUE to VAR if 'export VAR+=VALUE' is used.
New VAR is created if 'VAR+=' as in bash */
void	add_envp_variable(t_data *data, char *key, char *value, bool append)
{
	int		i;
	char	*new_var;

	new_var = ft_strjoin(key, value);
	if (!new_var)
		return ;
	i = -1;
	while (data->m_envp[++i])
	{
		if (ft_strncmp(data->m_envp[i], key, ft_strlen(key)) == 0)
		{
			if (append)
			{
				free(new_var);
				new_var = ft_strjoin(data->m_envp[i], value);
			}
			free(data->m_envp[i]);
			data->m_envp[i] = new_var;
			return ;
		}
	}
	if (i < BUFFER - 1)
		data->m_envp[i] = new_var;
	else
		free(new_var);
}

/* modified version of strchr(), returns index of first occurance of c */
int	ft_strchr_i(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
