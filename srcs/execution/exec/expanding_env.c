/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/18 23:36:06 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_buffer
{
	char	new_str[BUFFER];
	char	value[BUFFER];
	char	**arg;
	char	*tmp;
	int		k_len;
}	t_buffer;

static void	replace_value(char *str, int k_len, char *value, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str && *str != '$')
	{
		new_str[j++] = *(str++);
	}
	i = 0;
	while (value[i])
	{
		new_str[j++] = value[i++];
	}
	str = str + k_len + 1;
	while (*str)
	{
		new_str[j++] = *(str++);
	}
	new_str[j] = '\0';
}

static void	look_up_env(char *str, int k_len, char **env, char *value)
{
	char	*key;
	int		i;

	ft_bzero(value, BUFFER);
	while (*str && *str != '$')
		str++;
	if (!str || !env)
		return ;
	key = str + 1;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], k_len) && env[i][k_len] == '=')
		{
			ft_strcpy(value, env[i] + k_len + 1);
			return ;
		}
		i++;
	}
}

void	expand_envp(t_data *data, t_cmd_node *cmd_node)
{
	t_buffer	buf;
	int			i;
	int			j;

	buf.arg = cmd_node->argument;
	i = -1;
	while (buf.arg && buf.arg[++i])
	{
		j = -1;
		while (cmd_node->arg_subst[i][++j] > 0)
		{
			buf.k_len = cmd_node->arg_subst[i][j];
			if (buf.k_len == 1 && buf.arg[i][1] == '?')
				buf.tmp = ft_itoa(data->exit_code);
			else
			{
				look_up_env(buf.arg[i], buf.k_len, data->m_envp, buf.value);
				replace_value(buf.arg[i], buf.k_len, buf.value, buf.new_str);
				buf.tmp = ft_strdup(buf.new_str);
			}
			free(cmd_node->argument[i]);
			cmd_node->argument[i] = ft_strdup(buf.tmp);
			free(buf.tmp);
		}
	}
}
