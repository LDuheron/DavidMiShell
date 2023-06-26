/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:44 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 17:44:29 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// GET_CONTENT : This function copies "size" characters from src
// to dst from the position "start".

int	get_content(char *dst, char *src, unsigned int size, unsigned int start)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = start;
	if (size > 0)
	{
		while (src[i] && j < size)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (0);
}

void	init_data_lexing_structure(t_data_lexing *data_lexing, char *argv)
{
	data_lexing->line = NULL;
	data_lexing->line = ft_strjoin(data_lexing->line, argv);
	data_lexing->len = ft_strlen(data_lexing->line);
	data_lexing->d_tab_tmp = NULL;
	data_lexing->pos = 0;
}

// IS_REDIRECTION : This functions returns 0 if the given string 
// contains a redirection, else, it returns the corresponding 
// enum_type_token code.

int	is_redirection(t_data_lexing *data_lexing)
{
	char	*string;
	int		type;

	string = malloc(sizeof(char) * 3);
	string[0] = (*data_lexing).line[(*data_lexing).pos];
	if ((*data_lexing).line[(*data_lexing).pos + 1])
		string[1] = (*data_lexing).line[(*data_lexing).pos + 1];
	else
		string[1] = '\0';
	string[2] = '\0';
	if (ft_strncmp(string, "<<", 2) == 0)
		type = DOUBLE_IN;
	else if (ft_strncmp(string, ">>", 2) == 0)
		type = DOUBLE_OUT;
	else if (ft_strncmp(string, "<", 1) == 0)
		type = SIMPLE_IN;
	else if (ft_strncmp(string, ">", 1) == 0)
		type = SIMPLE_OUT;
	else
		type = N_DEF;
	free (string);
	return (type);
}
