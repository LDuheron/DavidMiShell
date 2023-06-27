/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:48:26 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/27 19:37:40 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_lst_token(t_tokens *token)
{
	t_tokens	*tmp;
	int			i;

	tmp = token;
	i = 0;
	printf("PRINT LST TOKEN\n");
	if (tmp == NULL)
	{
		printf("List is empty.\n");
		return ;
	}
	while (tmp != NULL)
	{
		printf("TOKEN NUMBER %i\n", i);
		printf("Content: %s\n", tmp->content);
		printf("Type : %i\n", tmp->type);
		printf("Len : %i\n\n", tmp->len);
		tmp = tmp->next;
		i++;
	}
}

/*
*/

char* enum_string(enum e_type_token value) {
	switch (value) {
		case N_DEF: return "N_DEF";
		case WORD: return "WORD";
		case PIPE: return "PIPE";
		case SINGLE_QUOTE: return "SINGLE_QUOTE";
		case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
		case SIMPLE_IN: return "SIMPLE_IN";
		case SIMPLE_OUT: return "SIMPLE_OUT";
		case DOUBLE_IN: return "DOUBLE_IN";
		case DOUBLE_OUT: return "DOUBLE_OUT";
		default: return "Unknown";
	}
}

void	print_cmd_node(t_cmd_node *cmd_node)
{
	int	i;
	int	j;

	printf("..print_cmd_node..\n");
	i = 0;
	j = 0;
	if (cmd_node == NULL)
	{
		printf("Error: cmd_node is NULL\n");
		return ;
	}
	/*
	if (cmd_node->argument)
	{
		//printf("\tCmd : %s\n", cmd_node->argument[0]); // cmd 'name'
		printf("\targ_subst : \n"); // cmd 'name'
		while (cmd_node->arg_subst[0][j] != -2)
		{
			printf("\t[0][%i] : %i\n\n", j, cmd_node->arg_subst[0][j]);
			j++;
		}
	}
	*/
	if (cmd_node->argument != NULL)
	{
		printf("\targument : \n");
		while (cmd_node->argument[i])
		{
			j = 0;
			printf("\t[%i] : [%s]", i, cmd_node->argument[i]);
			while (cmd_node->arg_subst[i][j] != -2)
			{
				//printf("\t\targ_substr[%i][%i] : [%s]", i, j, enum_string(cmd_node->arg_subst[i][j]));
				printf("\t\targ_substr[%i][%i] : key_len[%i]", i, j, cmd_node->arg_subst[i][j]);
				j++;
			}
			i++;
			printf("\n");
		}
	}
	i = 0;
	printf("\n");
	if (cmd_node->redir != NULL)
	{
		//printf("\tredir : \n");
		while (cmd_node->redir[i])
		{
			j = 0;
			printf("\tredir[%i] : [%s]", i, cmd_node->redir[i]);
			printf("\trdr_type[%i] : [%s]\n", i, enum_string(cmd_node->redir_type[i]));
			//printf("Redirection_type[%i] : %i\n", i, (cmd_node->redir_type[i]));
			while (cmd_node->redir_sub[i][j] != -2)
			{
				printf("\t\tRedir_sub[%i][%i] : [%i]\n", i, j, cmd_node->redir_sub[i][j]);
				j++;
			}
			i++;
		}
	}
}

void	print_cmd_lst(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*tmp;
	int			i;

	printf("\nPRINT cmd_lst : \n\n");
	tmp = *cmd_lst;
	i = 0;
	while (tmp)
	{
		printf(" ----- NODE %i ----- \n", i);
		printf("type : %i\n", tmp->type);
		if (tmp->type == CMD_NODE)
			print_cmd_node(tmp->cmd_node);
		printf("\n\n");
		if (!tmp->next)
			break ;
		i++;
		tmp = tmp->next;
	}
}
