/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:08:36 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 10:10:33 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_before_redir(int type_current, int type_next)
{
	if (type_next == PIPE)
		if (type_current == SIMPLE_IN || type_current == SIMPLE_OUT
			|| type_current == DOUBLE_IN || type_current == DOUBLE_OUT)
			return (1);
	return (0);
}

int	tok_is_op(t_tokens *tok)
{
	return (tok->type == SIMPLE_IN || tok->type == SIMPLE_OUT
		|| tok->type == DOUBLE_IN || tok->type == DOUBLE_OUT
		|| tok->type == PIPE);
}
