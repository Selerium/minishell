# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 15:46:23 by jadithya          #+#    #+#              #
#    Updated: 2023/07/18 15:57:09 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

CC := cc

SRCDIR := src
OBJDIR := obj
B_SRCDIR := bonussrcs
B_OBJDIR := bonusobjs

NAME := minishell

SRCS := $(SRCDIR)/minishell.c
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

B_SRCS := 
B_OBJS := $(B_SRCS:$(B_SRCDIR)/%.c=$(B_OBJDIR)/%.o)

CFLAGS := -g3 -Wall -Wextra -Werror

all: $(NAME)

bonus: $(BONUS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BONUS): $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(B_OBJS): $(B_SRCS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJDIR)/*.o $(B_OBJDIR)/*.o

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

norm:
	@echo "Mandatory:"
	@python3 -m norminette $(SRCS) include/minishell.h

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all bonus clean fclean re norm valgrind