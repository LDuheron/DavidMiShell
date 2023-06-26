/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:42:33 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/21 23:51:53 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. recuperer l'env
// a.fonction our trouver la taille de lenv
// b. fonction pour initialiser la liste qui accueille
// l'env : malloc + la remplir.

void	ft_lstadd_back_env_lst(t_env_lst **env_lst, t_env_lst *new)
{
	t_env_lst	*tmp;

	tmp = NULL;
	tmp = *env_lst;
	if (!*env_lst)
		*env_lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	get_size_env(char **env, t_env_lst **env_lst)
{
	t_env_lst	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp->content = malloc(sizeof(char) * (ft_strlen(env[i])));
		if (!tmp)
			return (ERROR_MALLOC);
		tmp->content = ft_strdup(env[i]);
		tmp->next = NULL;
		ft_lstadd_back_env_lst(env_lst, tmp);
		i++;
	}
	return (SUCCESS);
}

void	print_env_lst(t_env_lst **env_lst)
{
	t_env_lst	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		printf("%s", tmp->content);
		tmp = tmp->next;
	}
}

int	expand(t_cmd_lst **cmd_lst, char **env)
{
	t_env_lst	*env_lst;

	(void)cmd_lst;
	env_lst = malloc(sizeof(t_env_lst));
	if (!env)
		return (ERROR_MALLOC);
	env_lst = NULL;
	get_size_env(env, &env_lst);
	fill_env_lst(env, &env_lst);
	print_env_lst(&env_lst);
	return (SUCCESS);
}
