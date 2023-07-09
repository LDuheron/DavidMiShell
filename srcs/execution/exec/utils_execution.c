/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/09 18:38:52 by sbocanci         ###   ########.fr       */
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

/*
int	look_up_key_value(char *key, char *value, const char **m_envp)
{
	int j;
	int	key_len;
	int	value_len;

	key_len = ft_strlen(key);
	value_len = 0;
	j = 0;
	while (m_envp[j])
	{
		if (strncmp(key, m_envp[j], key_len) == 0 && m_envp[j][key_len] == '=')
		{
			value_len = ft_strlen(m_envp[j]) - key_len - 1;
			strncpy(value, m_envp[j] + key_len + 1, value_len);
			value[value_len] = '\0';
			return (value_len);
			break;
		}
		value[0] = '\0';
		j++;
	}
}

int	get_key_and_look_up_value(t_cmd_data *cmd, int j, int *output_len, const char **m_envp)
{
	int key_len;
	int value_len;
	char key[2048];
	char value[2048];

	key_len = 0;
	value_len = 0;
	j++;
	while (isalnum(cmd->input[j]) || cmd->input[j] == '_')
	{
		key[key_len++] = cmd->input[j++];
	}
	key[key_len] = '\0';
	//printf("\tkey: [%s], len: [%d]\t", key, key_len);

	value_len = look_up_key_value(key, value, m_envp);

	//printf("\tvalue: [%s], len: [%d]\n", value, value_len);

	strcat(cmd->output, value);
	*output_len += value_len;
	return (key_len);
}
*/

/* ..in this f() we extract the value from envp..
** need to add another f() to replace the old str with the new one with the value */
char	*look_up_key_and_replace(char *str, int key_len, char **m_envp)
{
	char	*new_str;
	char	*key;
	char	*value;
	int		i;

	value = NULL;
	new_str = NULL;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	key = ft_substr(str, i + 1, key_len);	
	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(key, m_envp[i], key_len) == 0 && m_envp[i][key_len] == '=')
		{
			value = ft_strdup(m_envp[i] + key_len + 1);
			break ;
		}
		i++;
	}
	printf("\t\tkey: [%s]\tvalue: [%s]\tstr: [%s], new_str: [%s]\n", key, value, str, new_str);
	free(key);
	free(value);
	return (new_str);
}

void	expand_envp(t_cmd_node *cmd_node, char **m_envp)
{
	(void)m_envp;
	char	**argument;
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
			look_up_key_and_replace(argument[i], key_len, m_envp);
			j++;
		}
		i++;
	}
}
