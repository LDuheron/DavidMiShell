/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:31:32 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 19:11:46 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_cmd_lst_node(t_cmd_lst **cmd_lst, t_cmd_lst *new)
{
	t_cmd_lst	*tmp;

	tmp = NULL;
	tmp = *cmd_lst;
	if (!*cmd_lst)
		*cmd_lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// EAT_TOKEN : This function free the token after we worked on it
// and set the pointer to the next token

void	eat_token(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	tmp = *tokens;
	if (!tmp)
		return ;
	if (tokens)
		*tokens = (*tokens)->next;
	free(tmp);
}

int	nb_dollar(char *str)
{
	int	cpt;
	int	i;

	cpt = 0;
	i = 0;
	while (str[i])
	{
		cpt += is_dollar(str[i]);
		i++;
	}
	return (cpt);
}

// IS_SUBSTITUTABLE : This function returns -2 if the string doesn't contain
// any dollar, -1, if there is a dollar that doesn't need to be substitute as
// it is in quotes.Else, it returns the len of characters to substitute behind
// the dollar sign.

int	is_substitutable(char *str, int i_dollar)
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
	if (str[i] == '?')
		return (1);
	while (str[i] && (is_alpha(str[i]) == 1
			|| is_number(str[i]) == 1 || str[i] == 95))
	{
		size++;
		i++;
	}
	return (size);
}
