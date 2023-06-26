/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:33:34 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/24 19:19:43 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// In or out quote.

# define OUT 0
# define IN 1

# define ERROR_MALLOC -3
# define ERROR_SYNTAX -2
# define ERROR 0
# define SUCCESS 1

//////////////////////////////////////////////////////////////////
//																//
//								ENUM							//
//																//
//////////////////////////////////////////////////////////////////

enum e_type_exec
{
	CMD_NODE,
	PIPE_NODE
} ;

enum e_type_token
{
	N_DEF,
	WORD,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	SIMPLE_IN,
	SIMPLE_OUT,
	DOUBLE_IN,
	DOUBLE_OUT
} ;

//////////////////////////////////////////////////////////////////
//																//
//																//
//						STRUCTURES								//
//																//
//																//
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//																//
//						DATA STRUCTURES							//
//																//
//////////////////////////////////////////////////////////////////

typedef struct s_data_lexing				t_data_lexing;
typedef struct s_tokens						t_tokens;

struct s_data_lexing {
	int		flag;
	char	*line;
	int		pos;
	int		len;
	int		*d_tab_tmp;
};

struct s_tokens {
	enum e_type_token	type;
	int					len;
	char				*content;
	int					*dollars_tab;
	struct s_tokens		*next;
};

//////////////////////////////////////////////////////////////////
//																//
//						TREE STRUCTURES							//
//																//
//////////////////////////////////////////////////////////////////

typedef struct s_cmd_node					t_cmd_node;
typedef struct s_cmd_lst					t_cmd_lst;

struct s_cmd_node {
	char	**argument;
	int		**arg_subst;
	char	**redir;
	int		*redir_type;
	int		**redir_sub;
};

struct s_cmd_lst {
	enum e_type_exec			type;
	t_cmd_node					*cmd_node;
	t_cmd_lst					*next;
};

// Expand_structures ideas
typedef struct s_env_lst
{
	char				*content;
	struct s_env_lst	*next;
}	t_env_lst;

typedef struct s_expand
{
	char		*new_arg;
	int			i;
	int			j;
}		t_expand;

//////////////////////////////////////////////////////////////////
//																//
//																//
//							PROTOTYPES 							//
//																//
//																//
//////////////////////////////////////////////////////////////////

// Main.c
void		prompt(char **env);
int			main(int argc, char **argv, char **env);

// Print_cmd_lst.c
void		ft_print_lst_token(t_tokens *token);
void		print_cmd_node(t_cmd_node *cmd);
void		print_cmd_lst(t_cmd_lst **cmd_lst);

//////////////////////////////////////////////////////////////////
//																//
//                   	  IN LEXING DIR              	        //
//																//
//////////////////////////////////////////////////////////////////

// New_token_quote.c
t_tokens	*new_token_double_quote(t_data_lexing *data_lexing, int size);
t_tokens	*new_token_single_quote(t_data_lexing *data_lexing, int size);
void		quotes_trimming(char *buffer);

// New_token.c
t_tokens	*new_token_pipe(void);
t_tokens	*new_token(t_data_lexing *data_lexing, int type, int size);

// Lexing_type.c
t_tokens	*lexing_double_quote(t_data_lexing *data_lexing);
t_tokens	*lexing_redirection(t_data_lexing *data_lexing, int type,
				int size_redirection);
t_tokens	*lexing_single_quote(t_data_lexing *data_lexing);
t_tokens	*lexing_word(t_data_lexing *data_lexing, int type);

// Lexing.c
t_tokens	*which_new_token(t_data_lexing *data_lexing);
int			find_type(t_data_lexing **data_lexing);
int			lexing(t_tokens **token, char *argv);

// Quote_management.c
int			is_double_quote(char c);
int			is_single_quote(char c);
int			is_quote(char c);
int			double_quote_management(char *line, int start);
int			single_quote_management(char *line, int start);

// Syntax.c
int			check_line(char *str);
int			check_open_d_quote(char *str, int i);
int			check_open_s_quote(char *str, int i);
int			check_redirection_content(t_tokens **token);
int			check_syntax(t_tokens **tokens);

// Utils.c
int			get_content(char *dst, char *src, unsigned int size,
				unsigned int start);
void		init_data_lexing_structure(t_data_lexing *data_lexing, char *argv);
int			is_redirection(t_data_lexing *data_lexing);

//////////////////////////////////////////////////////////////////
//																//
//                 		IN PARSING DIR   		                //
//																//
//////////////////////////////////////////////////////////////////

// Free_parsing.c
void		free_arg_in_node(t_cmd_node *cmd_node);
void		free_redir_in_node(t_cmd_node *cmd_node);
void		free_cmd_node(t_cmd_node *cmd_node);
void		free_cmd_lst(t_cmd_lst **cmd_lst);

// Init_cmd_node.c
void		set_cmd_node_to_null(t_cmd_node *cmd_node);
int			init_arg_tab(t_cmd_lst *cmd_lst, int i_arg);
int			init_redir_tab(t_cmd_lst *cmd_lst, int i_redir);
int			init_cmd_node(t_tokens **token, t_cmd_lst *cmd_lst);

// Get_arg.c
// int			fill_arg(t_cmd_node *cmd_node, char *content, int i);
// int			fill_redirection(t_cmd_node *cmd_node, char *content,
				// int type, int i);
int			fill_cmd_node(t_tokens **token, t_cmd_node *cmd);
void		set_last_c_null(t_cmd_node *cmd_node, int i_arg, int i_redir);

// Parsing.c
int			parse_command(t_cmd_lst **cmd_lst, t_tokens **token);
int			parse_pipe(t_cmd_lst **cmd_lst, t_tokens **token);
int			parsing(t_cmd_lst **cmd_lst, t_tokens **token);

// Utils.c
void		ft_lstadd_back_cmd_lst_node(t_cmd_lst **cmd_lst, t_cmd_lst *new);
void		eat_token(t_tokens **tokens);
int			nb_dollar(char *str);
int			is_substitutable(char *str, int i_dollar);

//////////////////////////////////////////////////////////////////
//																//
//                 	 	 IN UTILS DIR   	                    //
//																//
//////////////////////////////////////////////////////////////////

// Error_management_in_parsing.c
int			free_data_lexing(t_data_lexing *data_lexing);
int			error_malloc(t_data_lexing *data_lexing);
int			error_in_line(t_data_lexing *data_lexing);
int			error_syntax(t_tokens **tokens, int type);
void		free_token_structure(t_tokens **tokens);

//////////////////////////////////////////////////////////////////
//																//
//                 	  	IN CMD_LST UTILS DIR   	                //
//																//
//////////////////////////////////////////////////////////////////

// Ft_strjoin.c
char		*ft_strjoin(char *s1, char *s2);

// Is_something.c
int			is_alpha(int c);
int			is_dollar(char c);
int			is_metacharacter(char c);
int			is_number(int c);
int			is_pipe(char c);

// Is_something_2.c
int			is_forbidden(char c);
int			is_sign(char c);
int			is_space(char c);

// Libft_utils.c
char		*ft_strdup(char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);

// List_utils.c
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(char *content);

int			prepare_substitution(char *content, t_data_lexing **data_lexing);
t_tokens	*add_new_token(t_data_lexing *data_lexing, char *content, int type);
int			fill_arg(t_cmd_node *cmd_node, t_tokens **token, int i);
int			fill_redirection(t_cmd_node *cmd_node, t_tokens **token, int i);
char		*adjust_content(t_data_lexing *data_lexing,
				char *content, int size);
char		*single_dollar_trimming(char *buffer);

#endif
