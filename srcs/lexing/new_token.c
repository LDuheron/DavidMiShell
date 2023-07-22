/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:44:26 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/22 14:16:52 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new_elem->content = ft_strdup_content(content);
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

/* PREPARE_SUBSTITUTION: This function fills the array with information
** regarding the dollars needed for expansion. Each dollar occupies a line
** in the array, and a code is associated with each dollar. 
** If the code is -2, it means there is no substitution, indicating the end
** of the array. 
** If the code is -1, it indicates a dollar that doesn't need to be interpreted.
** If the code is a positive digit, it represents the length of the character to
** be substituted.
*/
int	prepare_substitution(char *content, t_data_lexing **data_lexing)
{
	int	nb_subst;
	int	pos;
	int	j;

	j = 0;
	pos = 0;
	nb_subst = nb_dollar(content);
	if (nb_subst == 0)
		return (SUCCESS);
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

/* ADJUST_CONTENT: This function returns the given content with some
** adjustments to facilitate parsing and expansion. 
** First, it removes the dollars ($) from the line that do not need to
** be interpreted, such as in the case of $"something" and $'something'.
** Then, it counts the number of remaining dollars that need to be interpreted
** in order to allocate an array that will contain the required information to
** handle those dollars later. This array is filled in the prepared substitution
** function.
** Afterwards, using the quotes_trimming function, it removes all quotes from
** the content since we have already obtained all the necessary information
** related to the quotes.
** Finally, the function returns the adjusted content after these modifications.
*/
char	*adjust_content(t_data_lexing *data_lexing, char *content, int size)
{
	int		nb_subst;

	if (!content)
		return (NULL);
	content = single_dollar_trimming(content);
	nb_subst = nb_dollar(content);
	data_lexing->d_tab_tmp = malloc(sizeof (int) * (nb_subst + 1));
	if (!data_lexing->d_tab_tmp)
	{
		ft_putendl_fd("DavidMishell: error malloc", 2);
		free(content);
		return (NULL);
	}
	prepare_substitution(content, &data_lexing);
	quotes_trimming(content);
	data_lexing->pos += (size - ft_strlen(content));
	return (content);
}

/* NEW_TOKEN: This function creates a new token.
*/
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

/* NEW_TOKEN_PIPE: This function creates a new token for a pipe without
** allocating memory for the "pipe" character. We consider that the
** length and type of the token provide sufficient information.
*/
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
