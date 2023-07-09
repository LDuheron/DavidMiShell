/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/10 00:13:51 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	int			status;
	int			pid;
	t_cmd_lst	*cmd_lst;

	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		if (cmd_lst->out_file >= 0)
			close(cmd_lst->out_file);
		if (cmd_lst->in_file >= 0)
			close(cmd_lst->in_file);
		cmd_lst = cmd_lst->next;
	}
}

/* The folowing code expands the ENV variable, raw version, seems to be working 
** will need to cleen and optimize it a bit.. */
char	*replace_value(char *str, char *key, char *value)
{
	char	*new_str;
	int		k_len;
	int		v_len;
	int		i;
	int		j;
	//printf("\t\tkey: [%s]\tvalue: [%s]\tstr: [%s]\n", key, value, str);
	//printf("\t\tlen_key: [%ld]\tlen_value: [%ld]\tlen_str: [%ld]\n", ft_strlen(key), ft_strlen(value), ft_strlen(str));
	
	new_str = NULL;
	if (ft_strlen(str) == ft_strlen(key))
		return (value);
	v_len = ft_strlen(value);
	k_len = ft_strlen(key);
	new_str = malloc(ft_strlen(str) - k_len + v_len + 1);
	i = 0;
	//while (ft_strncmp(key, str + i, ft_strlen(key)))
	while (str[i] && str[i] != '$')
	{
		new_str[i] = str[i];
		i++;
	}
	j = -1;
	while (value[++j])
		new_str[i + j] = value[j];
	while (str[k_len + i])
	{
		new_str[v_len + i] = str[k_len + i];
		i++;
	}
	new_str[v_len + i] = '\0';
	/*
	*/
	free(value);
	return (new_str);
}

/* ..in this f() we extract the value from envp..
** need to add another f() to replace the old str with the new one with the value */
//char	*look_up_key_and_replace(char *str, int key_len, char **m_envp)
char	*look_up_key_value(char *str, int key_len, char **m_envp)
{
	char	*new_str;
	char	*key;
	char	*value;
	int		i;
	int		j;

	value = NULL;
	new_str = NULL;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	key = ft_substr(str, i, key_len + 1);	
	j = 0;
	while (m_envp[j])
	{
		if (ft_strncmp(key + 1, m_envp[j], key_len - 1) == 0 && m_envp[j][key_len] == '=')
		{
			value = ft_strdup(m_envp[j] + key_len + 1);
			break ;
		}
		j++;
	}
	if (!value)
		value = ft_strdup("");
	new_str = replace_value(str, key, value);

	//printf("\t\tstr: [%s]\tkey: [%s]\tvalue: [%s]\tnew_str: [%s]\n", str, key, value, new_str);

	//free(str);
	free(key);
	//free(value);
	return (new_str);
}

void	expand_envp(t_cmd_node *cmd_node, char **m_envp)
{
	(void)m_envp;
	char	**argument;
	char	*tmp;
	int		key_len;
	int		i;
	int		j;
	
	argument = cmd_node->argument;
	i = 0;
	while (argument[i])
	{
		j = 0;
		while (cmd_node->arg_subst[i][j] > 0)
		{
			key_len = cmd_node->arg_subst[i][j];
			tmp = look_up_key_value(argument[i], key_len, m_envp);
			argument[i] = tmp;
			j++;
		}
		i++;
	}
}
