/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:42:51 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/16 14:20:35 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	empty_buffer(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (false);
		str++;
	}
	return (true);
}

char	**get_path_directories(char **m_envp)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(m_envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (m_envp[i])
		path = ft_split(m_envp[i] + 5, ':');
	return (path);
}
