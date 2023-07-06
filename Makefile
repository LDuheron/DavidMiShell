#############################################

NAME := minishell

#############################################

#############################################

SRC_DIR     := srcs
OBJ_DIR     := obj
SRCS        := 											\
	libft/ft_putchar_fd.c								\
	libft/ft_putendl_fd.c								\
	libft/ft_putstr_fd.c								\
	libft/ft_strlen.c									\
	libft/ft_substr.c									\
	libft/ft_strdup.c									\
	libft/ft_strjoin.c									\
	libft/ft_split.c									\
	main.c												\
	print_cmd_lst.c 									\
	utils/cmd_lst_utils/error_management_in_parsing.c	\
	utils/cmd_lst_utils/is_something.c					\
	utils/cmd_lst_utils/is_something_2.c				\
	utils/cmd_lst_utils/libft_utils.c					\
	utils/free/ft_free.c								\
	utils/initialization/initialization.c				\
	utils/initialization/utils_init.c					\
	lexing/syntax.c										\
	lexing/lexing_type.c     							\
	lexing/lexing.c    									\
	lexing/new_token_quote.c    						\
	lexing/new_token.c    								\
	lexing/quote_management.c							\
	lexing/utils.c										\
	parsing/free_parsing.c								\
	parsing/fill_cmd_node.c								\
	parsing/init_cmd_node.c								\
	parsing/parsing.c									\
	parsing/utils.c										\
	signals/signal_handler.c							\
	execution/exec/execution.c							\
	execution/exec/ft_exec.c							\
	execution/exec/utils_execution.c					\
	execution/builtin/ft_cd.c							\
	execution/builtin/ft_echo.c							\
	execution/builtin/ft_env.c							\
	execution/builtin/ft_exit.c							\
	execution/builtin/ft_export.c						\
	execution/builtin/ft_pwd.c							\
	execution/builtin/ft_unset.c						\
	execution/builtin/utils_builtin.c					\

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3
CPPFLAGS    := -I include

#############################################

RM          := rm -f
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#############################################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline 
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
#  $(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#############################################

.PHONY: clean fclean re

.SILENT:

#############################################