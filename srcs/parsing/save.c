/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:57:09 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 18:16:25 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ADD NEW TOKEN : Creates a new token (Like a ft_lstnew but with type).
t_tokens	*add_new_token_old(char *content, int type)
{
	t_tokens	*new_elem;

	new_elem = malloc (sizeof(t_tokens));
	if (new_elem == NULL)
		return (NULL);
	new_elem->type = type;
	if (content != NULL)
	{
		new_elem->len = ft_strlen(content);
		new_elem->content = ft_strdup(content);
		new_elem->dollars_tab = NULL;
	}
	else
	{
		new_elem->len = 0;
		new_elem->content = NULL;
		new_elem->dollars_tab = NULL;
	}
	new_elem->next = NULL;
	return (new_elem);
}

int	fill_arg_save(t_cmd_node *cmd_node, char *content, int i)
{
	int	nb_subst;
	int	j;

	j = 0;
	nb_subst = nb_dollar(content);
	cmd_node->argument[i] = ft_strdup(content);
	cmd_node->arg_subst[i] = malloc(sizeof (int) * (nb_subst + 1));
	if (!cmd_node->arg_subst[i])
		return (ERROR_MALLOC);
	cmd_node->arg_subst[i][nb_subst] = -2;
	while (j < nb_subst)
	{
		cmd_node->arg_subst[i][j] = -5;
		cmd_node->arg_subst[i][j] = is_substitutable(cmd_node->argument[i],
				j + 1);
		j++;
	}
	return (SUCCESS);
}

int	fill_redirection_save(t_cmd_node *cmd_node, char *content, int type, int i)
{
	int	nb_subst;
	int	j;

	j = 0;
	nb_subst = nb_dollar(content);
	cmd_node->redir[i] = ft_strdup(content);
	cmd_node->redir_type[i] = type;
	cmd_node->redir_sub[i] = malloc(sizeof (int) * (nb_subst + 1));
	if (!cmd_node->redir_sub[i])
		return (ERROR_MALLOC);
	cmd_node->redir_sub[i][nb_subst] = -2;
	while (j < nb_subst)
	{
		cmd_node->redir_sub[i][j] = -2;
		cmd_node->redir_sub[i][j] = is_substitutable(cmd_node->redir[i], j + 1);
		j++;
	}
	return (SUCCESS);
}

// IS_SUBSTITUTABLE : This function returns -2 if the string doesn't contain
// any dollar, -1, if there is a dollar that doesn't need to be substitute as
// it is in quotes.Else, it returns the len of characters to substitute behind
// the dollar sign.

int	is_substitutable_save(char *str, int i_dollar)
{
	int	i;
	int	cpt_dollar;
	int	size;

	i = 0;
	cpt_dollar = 0;
	size = 0;
	while (cpt_dollar < i_dollar)
	{
		while (str[i] && is_dollar(str[i]) == 0)
			i++;
		if (!str[i])
			return (-2);
		i++;
		cpt_dollar++;
	}
	while (str[i] && (is_alpha(str[i]) == 1
			|| is_number(str[i]) == 1 || str[i] == 95))
	{
		size++;
		i++;
	}	
	return (size);
}
