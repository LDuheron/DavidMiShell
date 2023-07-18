/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/18 09:40:51 by sbocanci         ###   ########.fr       */
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

/*
char	*replace_value(char *str, char *key, char *value)
{
	char	*new_str;
	int		k_len;
	int		v_len;
	int		i;
	int		j;

	v_len = ft_strlen(value);
	k_len = ft_strlen(key) + 1;
	new_str = malloc(ft_strlen(str) - k_len + v_len + 1);
	i = -1;
	while (str[++i] && str[i] != '$')
		new_str[i] = str[i];
	j = -1;
	while (value[++j])
		new_str[i + j] = value[j];
	while (str[k_len + i])
	{
		new_str[v_len + i] = str[k_len + i];
		i++;
	}
	new_str[v_len + i] = '\0';
	free(value);
	return (new_str);
}

char	*look_up_key_value(char *str, int k_len, char **env)
{
	char	*new_str;
	char	*key;
	char	*value;
	int		i;

	new_str = NULL;
	value = ft_strdup("");
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	key = ft_substr(str, i + 1, k_len);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], k_len) && env[i][k_len] == '=')
		{
			free(value);
			value = ft_strdup(env[i] + k_len + 1);
			break ;
		}
	}
	if (ft_strcmp(str + 1, key) == 0)
		new_str = value;
	else
		new_str = replace_value(str, key, value);
	free(key);
	return (new_str);
}

void	expand_envp(t_data *data, t_cmd_node *cmd_node)
{
	char	*tmp;
	int		key_len;
	int		i;
	int		j;

	i = 0;
	while (cmd_node->argument && cmd_node->argument[i])
	{
		j = 0;
		while (cmd_node->arg_subst[i][j] > 0)
		{
			key_len = cmd_node->arg_subst[i][j];
			if (key_len == 1 && cmd_node->argument[i][1] == '?')
				tmp = ft_itoa(data->exit_code);
			else
				tmp = look_up_key_value(cmd_node->argument[i],
						key_len, data->m_envp);
			cmd_node->argument[i] = tmp;
			j++;
		}
		i++;
	}
}
*/