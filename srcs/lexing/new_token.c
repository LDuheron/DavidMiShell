/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:44:26 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 19:17:06 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//// messageerror malloc das fill arg et fill redirections

// IS_NOT_INTERPRETED_DOLLAR : This functions search if the sent dollar
// is between single quote.

int	is_not_interpreted_dollar(char *str, int pos_dollar)
{
	int	i;
	int	flag;

	i = 0;
	flag = OUT;
	while (str[i] && i < pos_dollar)
	{
		if (is_single_quote(str[i]))
		{
			if (flag == IN)
				flag = OUT;
			else
				flag = IN;
		}
		i++;
	}
	if (flag == IN)
		return (1);
	return (OUT);
}

int	prepare_substitution(char *content, t_data_lexing **data_lexing)
{
	int	nb_subst;
	int	pos;
	int	j;

	j = 0;
	pos = 0;
	nb_subst = nb_dollar(content);
	(*data_lexing)->d_tab_tmp[nb_subst] = -2;
	while (j < nb_subst && content[pos])
	{
		while (content[pos] != '$')
			pos++;
		(*data_lexing)->d_tab_tmp[j] = -2;
		if (is_not_interpreted_dollar(content, pos) == 1)
			(*data_lexing)->d_tab_tmp[j] = -1;
		else
			(*data_lexing)->d_tab_tmp[j] = is_substitutable(content, j + 1);
		j++;
		pos++;
	}
	return (SUCCESS);
}

t_tokens	*add_new_token(t_data_lexing *data_lexing, char *content, int type)
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
		new_elem->dollars_tab = data_lexing->d_tab_tmp;
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

// NEW TOKEN : Create a new token when then input 
// is not a word, a quote, or a parenthesis.
t_tokens	*new_token(t_data_lexing *data_lexing, int type, int size)
{
	char	*content;

	content = NULL;
	if (size > 0)
	{
		content = malloc(sizeof(char *) * (size + 1));
		if (content == NULL)
		{
			free(content);
			return (NULL);
		}
		get_content(content, data_lexing->line, size, data_lexing->pos);
	}
	content = adjust_content(data_lexing, content, size);
	return (add_new_token(data_lexing, content, type));
}

char	*adjust_content(t_data_lexing *data_lexing, char *content, int size)
{
	int		nb_subst;

	content = single_dollar_trimming(content);
	nb_subst = nb_dollar(content);
	data_lexing->d_tab_tmp = malloc(sizeof (int) * (nb_subst + 1));
	if (!data_lexing->d_tab_tmp)
	{
		printf("minishell: error malloc\n");
		free(content);
		return (NULL);
	}
	prepare_substitution(content, &data_lexing);
	quotes_trimming(content);
	data_lexing->pos += (size - ft_strlen(content));
	return (content);
}

// NEW TOKEN PIPE : Creates a new token for pipe without 
// allocating memory for the character pipe as we consider
// that the len and the types are transmitting enough informations already.

t_tokens	*new_token_pipe(void)
{
	t_tokens	*new_elem;

	new_elem = malloc (sizeof(t_tokens));
	if (new_elem == NULL)
		return (NULL);
	new_elem->type = PIPE;
	new_elem->len = 1;
	new_elem->content = NULL;
	new_elem->next = NULL;
	new_elem->dollars_tab = NULL;
	return (new_elem);
}
