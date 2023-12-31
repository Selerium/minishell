# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 15:46:23 by jadithya          #+#    #+#              #
#    Updated: 2023/10/11 20:24:52 by jebucoy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

CC := cc

BUILTINS := builtins
PARSING	:=	parsing
EXPANSION := expansion
QUOTES := quotes
SRCDIR := src
OBJDIR := obj
B_SRCDIR := bonussrcs
B_OBJDIR := bonusobjs

NAME := minishell

SRCS := $(SRCDIR)/minishell.c\
		$(SRCDIR)/env_vars.c\
		$(SRCDIR)/signals.c\
		$(SRCDIR)/run_cmds.c\
		$(SRCDIR)/find_cmd.c\
		$(SRCDIR)/execute_cmd.c\
		$(SRCDIR)/cleanup.c\
		$(SRCDIR)/redirs.c\
		$(SRCDIR)/redirs_2.c\
		$(SRCDIR)/free.c\
		$(SRCDIR)/$(BUILTINS)/pwd.c\
		$(SRCDIR)/$(BUILTINS)/export.c\
		$(SRCDIR)/$(BUILTINS)/cd.c\
		$(SRCDIR)/$(BUILTINS)/echo.c\
		$(SRCDIR)/$(BUILTINS)/unset.c\
		$(SRCDIR)/$(BUILTINS)/exit.c\
		$(SRCDIR)/$(BUILTINS)/env.c\
		$(SRCDIR)/$(BUILTINS)/miniminishell.c\
		$(SRCDIR)/$(PARSING)/syntax_check.c\
		$(SRCDIR)/$(PARSING)/handle_flags.c\
		$(SRCDIR)/$(PARSING)/split_input.c\
		$(SRCDIR)/$(PARSING)/utils.c\
		$(SRCDIR)/$(PARSING)/my_split.c\
		$(SRCDIR)/$(PARSING)/get_redir.c\
		$(SRCDIR)/$(EXPANSION)/expansion_utils.c \
		$(SRCDIR)/$(QUOTES)/quotes.c

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

B_SRCS := 

B_OBJS := $(B_SRCS:$(B_SRCDIR)/%.c=$(B_OBJDIR)/%.o)

ifeq (${OS}, Darwin)
	CFLAGS := -g3 -Wall -Wextra -Werror -I/Users/jebucoy/.brew/opt/readline/include -g3
	LINKERS := -lreadline -L/Users/jebucoy/.brew/opt/readline/lib
else
	CFLAGS := -g3 -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3 -D LINUX
	LINKERS := -lreadline -L/usr/local/opt/readline/lib
endif

LIB := libft/libft.a

all: $(NAME)

bonus: $(BONUS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/$(BUILTINS):
	mkdir -p $(OBJDIR)/$(BUILTINS)

$(OBJDIR)/$(PARSING):
	mkdir -p $(OBJDIR)/$(PARSING)

$(OBJDIR)/$(EXPANSION):
	mkdir -p $(OBJDIR)/$(EXPANSION)

$(OBJDIR)/$(QUOTES):
	mkdir -p $(OBJDIR)/$(QUOTES)

$(NAME): $(OBJDIR) $(OBJDIR)/$(BUILTINS) $(OBJDIR)/$(PARSING) $(OBJDIR)/$(EXPANSION) $(OBJDIR)/$(QUOTES) $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LINKERS) $(LIB) -o $@

$(BONUS): $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(B_OBJS): $(B_SRCS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB):
	make bonus -C libft

clean:
	make clean -C libft
	rm -rf $(OBJDIR) $(B_OBJDIR)

fclean: clean
	rm -f $(LIB)
	rm -f $(NAME) $(BONUS)

re: fclean all

norm:
	@echo "Mandatory:"
	@python3 -m norminette $(SRCS) include/minishell.h

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valsupp.sup ./minishell

.PHONY: all bonus clean fclean re norm valgrind