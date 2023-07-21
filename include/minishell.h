/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:52:39 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/21 16:36:54 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

extern int	g_status;

// In or out quote.

# define OUT 0
# define IN 1

# define ERROR_MALLOC -3
# define ERROR_SYNTAX -2
# define ERROR 0
# define SUCCESS 1
# define BUFFER 2048
# define HD_FILE "/tmp/dm_here_doc_tmp_file"

//////////////////////////////////////////////////////////////////
//																//
//								ENUM							//
//																//
//////////////////////////////////////////////////////////////////

enum e_type_exec
{
	CMD_NODE,
	PIPE_NODE
};

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
};

enum e_builtin
{
	N_A,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
};

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

typedef struct s_data_lexing {
	char	*line;
	int		pos;
	int		len;
	int		*d_tab_tmp;
}	t_data_lexing;

typedef struct s_tokens {
	enum e_type_token	type;
	int					len;
	char				*content;
	int					*dollars_tab;
	struct s_tokens		*next;
}	t_tokens;

//////////////////////////////////////////////////////////////////
//																//
//						TREE STRUCTURES							//
//																//
//////////////////////////////////////////////////////////////////

typedef struct s_cmd_node {
	char	**argument;
	int		**arg_subst;
	char	**redir;
	int		*redir_type;
	int		**redir_sub;
}	t_cmd_node;

typedef struct s_cmd_lst {
	enum e_type_exec	type;
	t_cmd_node			*cmd_node;
	int					in_file;
	int					out_file;
	struct s_cmd_lst	*next;
}	t_cmd_lst;

typedef struct s_data
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;
	char		**env;
	char		**m_envp;
	char		**path_dirs;
	int			exit_code;
	int			pid;
}	t_data;

//////////////////////////////////////////////////////////////////
//																//
//																//
//							PROTOTYPES 							//
//																//
//																//
//////////////////////////////////////////////////////////////////

/* Main.c */
void		prompt(t_data *data);
int			main(int argc, char **argv, char **env);

/* Print_cmd_lst.c
void		ft_print_lst_token(t_tokens *token);
void		print_cmd_node(t_cmd_node *cmd);
void		print_cmd_lst(t_cmd_lst **cmd_lst);
char		*ft_put_enum(int type);
*/

//////////////////////////////////////////////////////////////////
//																//
//                   	  IN LEXING DIR              	        //
//																//
//////////////////////////////////////////////////////////////////

/* Lexing_type.c */
t_tokens	*lexing_double_quote(t_data_lexing *data_lexing);
t_tokens	*lexing_single_quote(t_data_lexing *data_lexing);
t_tokens	*lexing_redirection(t_data_lexing *data_lexing, int type,
				int size_redirection);
t_tokens	*lexing_word(t_data_lexing *data_lexing, int type);

/* Lexing.c */
t_tokens	*which_new_token(t_data_lexing *data_lexing);
int			find_type(t_data_lexing **data_lexing);
int			lexing(t_tokens **token, char *argv);

/* New_token_quote.c */
char		*single_dollar_trimming(char *buffer);
void		quotes_trimming(char *buffer);
t_tokens	*new_token_double_quote(t_data_lexing *data_lexing, int size);
t_tokens	*new_token_single_quote(t_data_lexing *data_lexing, int size);

/* New_token.c */
t_tokens	*add_new_token(t_data_lexing *data_lexing, char *content, int type);
int			prepare_substitution(char *content, t_data_lexing **data_lexing);
char		*adjust_content(t_data_lexing *data_lexing,
				char *content, int size);
t_tokens	*new_token(t_data_lexing *data_lexing, int type, int size);
t_tokens	*new_token_pipe(void);

/* Quote_management.c */
int			is_double_quote(char c);
int			is_single_quote(char c);
int			is_quote(char c);
int			double_quote_management(char *line, int start);
int			single_quote_management(char *line, int start);

/* Syntax_utils.c */
int			is_pipe_before_redir(int type_current, int type_next);
int			tok_is_op(t_tokens *tok);
int			tok_is_redir(t_tokens *tok);

/* Syntax.c */
int			check_syntax(t_data *data, t_tokens **tokens);
int			check_open_s_quote(char *str, int i);
int			check_open_d_quote(char *str, int i);
int			check_line(char *str);

/* Trimming_utils.c */
int			single_dollar_trimming_utils(char *buffer, int i);
int			single_quotes_trimming_utils(char *buffer, int i);
int			double_quotes_trimming_utils(char *buffer, int i);

/* Utils.c */
int			get_content(char *dst, char *src, unsigned int size,
				unsigned int start);
void		init_data_lexing_structure(t_data_lexing *data_lexing, char *argv);
int			is_redirection(t_data_lexing *data_lexing);
int			is_not_interpreted_dollar(char *str, int pos_dollar);
void		ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new);

//////////////////////////////////////////////////////////////////
//																//
//                 		IN PARSING DIR   		                //
//																//
//////////////////////////////////////////////////////////////////

/* fill_cmd_node.c */
int			fill_arg(t_cmd_node *cmd_node, t_tokens **token, int i);
int			fill_redirection(t_cmd_node *cmd_node, t_tokens **token, int i);
void		set_last_c_null(t_cmd_node *cmd_node, int i_arg, int i_redir);
int			fill_cmd_node(t_tokens **token, t_cmd_node *cmd);

/* Free_parsing.c */
void		node_destroy(t_cmd_lst *list);
void		list_destroy(t_cmd_lst *list);

/* Init_cmd_node.c */
void		set_cmd_node_to_null(t_cmd_node *cmd_node);
int			init_arg_tab(t_cmd_lst *cmd_lst, int i_arg);
int			init_redir_tab(t_cmd_lst *cmd_lst, int i_redir);
int			init_cmd_node(t_tokens **token, t_cmd_lst *cmd_lst);

/* Parsing.c */
int			parse_command(t_cmd_lst **cmd_lst, t_tokens **token);
int			parse_pipe(t_cmd_lst **cmd_lst, t_tokens **token);
int			parsing(t_cmd_lst **cmd_lst, t_tokens **token);

/* Utils.c */
void		ft_lstadd_back_cmd_lst_node(t_cmd_lst **cmd_lst, t_cmd_lst *new);
void		eat_token(t_tokens **tokens);
int			nb_dollar(char *str);
int			is_substitutable(char *str, int i_dollar);

//////////////////////////////////////////////////////////////////
//																//
//                 	 	 IN SIGNALS DIR   	                    //
//																//
//////////////////////////////////////////////////////////////////

/* signal_handler.c */
void		sigint_handler(int sig);
void		ft_signal_child(int signal);

//////////////////////////////////////////////////////////////////
//																//
//                 	  	IN CMD_LST UTILS DIR   	                //
//																//
//////////////////////////////////////////////////////////////////

/* Error_management_in_parsing.c */
void		free_token_structure(t_tokens **tokens);
int			error_malloc(t_data_lexing *data_lexing);
int			error_in_line(t_data_lexing *data_lexing);
int			free_data_lexing(t_data_lexing *data_lexing);
int			error_syntax(t_data *data, t_tokens **tokens, t_tokens *tmp);

/* Ft_strdup_content.c */
char		*ft_strdup_content(char *src);

/* Ft_strjoin_content.c */
char		*ft_strjoin_content(char *s1, char *s2);

/* Is_something.c */
int			is_alpha(int c);
int			is_dollar(char c);
int			is_metacharacter(char c);
int			is_number(int c);
int			is_pipe(char c);

/* Is_something_2.c */
int			is_forbidden(char c);
int			is_sign(char c);
int			is_space(char c);
char		*convert_type_to_char(int type);

//////////////////////////////////////////////////////////////////
//																//
//                 	  	IN FREE UTILS DIR   	                //
//																//
//////////////////////////////////////////////////////////////////

/* ft_free.c */
void		free_tab(char **str);

//////////////////////////////////////////////////////////////////
//																//
//                	IN INITIALIZATION UTILS DIR   	            //
//																//
//////////////////////////////////////////////////////////////////

/* initialization.c */
void		init_data(t_data *data, char **env);

/* utils_init.c */
bool		empty_buffer(char *str);
char		**get_path_directories(char **m_envp);

//////////////////////////////////////////////////////////////////
//																//
//                 	  	IN EXECUTION EXEC DIR  	                //
//																//
//////////////////////////////////////////////////////////////////

/* execution.c */
void		execution(t_data *data);
void		ft_execve(t_data *data, t_cmd_lst *cmd_lst);

/* expending_env.c */
void		expand_envp(t_data *data, t_cmd_node *cmd_node);

/* ft_exec.c */
void		ft_launch_cmd(t_data *data, t_cmd_lst *cmd_lst);

/* redirection.c */
bool		set_redirection(t_data *data, t_cmd_lst *cmd_lst);
void		ft_here_doc(char *delimiter);

/* utils_execution.c */
void		ft_wait(t_data *data);
void		builtin_redirect_in_out(t_cmd_lst *cmd_lst, int *in, int *out);
void		builtin_close_in_out_files(t_cmd_lst *cmd_lst, int *in, int *out);

//////////////////////////////////////////////////////////////////
//																//
//                 	  	IN EXECUTION BUILTIN DIR  	            //
//																//
//////////////////////////////////////////////////////////////////

void		ft_cd(t_data *data, t_cmd_lst *cmd_lst);
int			settings_cd(t_cmd_lst *cmd_lst);
bool		too_many_arguments(t_data *data, t_cmd_lst *cmd_lst);
int			ft_echo(t_data *data, t_cmd_lst *cmd_lst);
int			ft_export(t_data *data, t_cmd_lst *cmd_lst);
int			ft_env(t_data *data);
int			ft_exit(t_data *data, t_cmd_lst *cmd_lst);
int			ft_pwd(t_data *data, t_cmd_lst *cmd_lst);
int			ft_unset(t_data *data, t_cmd_lst *cmd_lst);

/* utils_builtin.c */
int			check_builtin(t_cmd_lst *cmd_lst);
void		exec_builtin_child(t_data *data, t_cmd_lst *cmd_lst, int builtin);
void		exec_builtin(t_data *data, t_cmd_lst *cmd_lst, int builtin);
void		add_envp_variable(t_data *data, char *key, char *value,
				bool append);
int			ft_strchr_i(char *str, int c);

/* DEBUG FUNCTION */
char		*print_builtin(int builtin);
char		*print_node_type(int type);
/* ************** */

#endif
