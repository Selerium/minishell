# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 15:46:23 by jadithya          #+#    #+#              #
#    Updated: 2023/08/13 19:48:39 by jebucoy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

CC := cc

BUILTINS := builtins
PARSING	:=	parsing
SRCDIR := src
OBJDIR := obj
B_SRCDIR := bonussrcs
B_OBJDIR := bonusobjs

NAME := minishell

SRCS := $(SRCDIR)/minishell.c\
		$(SRCDIR)/env_vars.c\
		$(SRCDIR)/signals.c\
		$(SRCDIR)/$(BUILTINS)/pwd.c\
		$(SRCDIR)/$(BUILTINS)/export.c\
		$(SRCDIR)/$(BUILTINS)/cd.c\
		$(SRCDIR)/$(PARSING)/syntax_check.c\
		$(SRCDIR)/$(PARSING)/handle_flags.c\
		$(SRCDIR)/$(PARSING)/split_input.c\
		$(SRCDIR)/$(PARSING)/deboog.c\
		$(SRCDIR)/$(PARSING)/utils.c\

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

B_SRCS := 

B_OBJS := $(B_SRCS:$(B_SRCDIR)/%.c=$(B_OBJDIR)/%.o)

CFLAGS := -g3 -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3 -fsanitize=address

LINKERS := -lreadline -L/usr/local/opt/readline/lib

LIB := libft/libft.a

all: $(NAME)

bonus: $(BONUS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(BUILTINS)
	mkdir -p $(OBJDIR)/$(PARSING)

$(NAME): $(OBJDIR) $(OBJS) $(LIB)
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
	rm $(LIB)
	rm -f $(NAME) $(BONUS)

re: fclean all

norm:
	@echo "Mandatory:"
	@python3 -m norminette $(SRCS) include/minishell.h

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all bonus clean fclean re norm valgrind