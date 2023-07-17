/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/17 13:31:19 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	last_pid(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		data->exit_code = WTERMSIG(status) + 128;
		if (data->exit_code == 130)
			ft_putstr_fd("\n", STDERR_FILENO);
		if (data->exit_code == 131)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

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
			last_pid(data, status);
		if (cmd_lst->out_file >= 0)
			close(cmd_lst->out_file);
		if (cmd_lst->in_file >= 0)
			close(cmd_lst->in_file);
		cmd_lst = cmd_lst->next;
	}
	unlink(HD_FILE);
}

/* The folowing code expands the ENV variable, raw version,
seems to be working fine
*/
char	*replace_value(char *str, char *key, char *value)
{
	char	*new_str;
	int		k_len;
	int		v_len;
	int		i;
	int		j;

	v_len = ft_strlen(value);
	k_len = ft_strlen(key);
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
	key = ft_substr(str, i, k_len + 1);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(key + 1, env[i], k_len - 1) == 0 && env[i][k_len] == '=')
		{
			free(value);
			value = ft_strdup(env[i] + k_len + 1);
			break ;
		}
	}
	if (ft_strcmp(str, key) == 0)
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
