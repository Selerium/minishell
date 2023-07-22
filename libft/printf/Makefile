# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 22:13:13 by jadithya          #+#    #+#              #
#    Updated: 2023/06/13 13:48:43 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_digits.c\
		ft_hexdigits.c\
		ft_power.c\
		ft_precisionprint.c\
		ft_printchr.c\
		ft_printf.c\
		ft_printhex.c\
		ft_printhex2.c\
		ft_printnum.c\
		ft_printptrhex.c\
		ft_printspace.c\
		ft_printstr.c\
		ft_printunsint.c\
		ft_printzeros.c\

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast

DEPS = libftprintf.h\
		libft/libft.h\

OBJS = $(SRCS:.c=.o)

LIB = libft/libft.a

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS)
	make -C libft
	ar rcs $(NAME) $(OBJS) libft/*.o

bonus: 

all: $(NAME) bonus

clean:
	rm -f $(OBJS) libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all