#############################################

NAME := minishell
_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

#############################################

#############################################

SRC_DIR     := srcs
OBJ_DIR     := obj
SRCS        := 											\
	libft/ft_atoi.c										\
	libft/ft_atolong.c									\
	libft/ft_bzero.c									\
	libft/ft_itoa.c										\
	libft/ft_putchar_fd.c								\
	libft/ft_putendl_fd.c								\
	libft/ft_putstr_fd.c								\
	libft/ft_strlen.c									\
	libft/ft_strcat.c									\
	libft/ft_strcpy.c									\
	libft/ft_substr.c									\
	libft/ft_strdup.c									\
	libft/ft_strchr.c									\
	libft/ft_strncmp.c									\
	libft/ft_strcmp.c									\
	libft/ft_strjoin.c									\
	libft/ft_split.c									\
	main.c												\
	utils/cmd_lst_utils/error_management_in_parsing.c	\
	utils/cmd_lst_utils/is_something.c					\
	utils/cmd_lst_utils/is_something_2.c				\
	utils/cmd_lst_utils/ft_strjoin_content.c			\
	utils/cmd_lst_utils/ft_strdup_content.c				\
	utils/free/ft_free.c								\
	utils/initialization/initialization.c				\
	utils/initialization/utils_init.c					\
	lexing/syntax.c										\
	lexing/syntax_utils.c								\
	lexing/lexing_type.c     							\
	lexing/lexing.c    									\
	lexing/new_token_quote.c    						\
	lexing/new_token.c    								\
	lexing/quote_management.c							\
	lexing/trimming_utils.c								\
	lexing/utils.c										\
	parsing/free_parsing.c								\
	parsing/fill_cmd_node.c								\
	parsing/init_cmd_node.c								\
	parsing/parsing.c									\
	parsing/utils.c										\
	signals/signal_handler.c							\
	execution/exec/execution.c							\
	execution/exec/expanding_env.c						\
	execution/exec/ft_exec.c							\
	execution/exec/ft_here_doc.c						\
	execution/exec/redirection.c						\
	execution/exec/utils_execution.c					\
	execution/builtin/ft_cd.c							\
	execution/builtin/ft_cd_utils.c						\
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
#	$(info CREATED $(NAME))
	@printf "\e[92;5;118m\n>>> DavidMishell ready\n\e[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@printf "$(_CYAN)Generating $(NAME) objects...$(_BLUE)%-33.33s\r$(_NC)" $@

clean:
	$(RM) $(OBJS)
	@printf "\033[00;31m>>> objects removed.\n\033[00m"

fclean: clean
	$(RM) $(NAME)
	@printf "\033[00;31m>>> executable removed.\n\033[00m"

re:
	$(MAKE) fclean
	$(MAKE) all

#############################################

.PHONY: clean fclean re

.SILENT:

#############################################