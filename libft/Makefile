# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 13:42:18 by jadithya          #+#    #+#              #
#    Updated: 2023/06/15 15:18:14 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c

PRINTFSRC = printf/ft_digits.c\
			printf/ft_hexdigits.c\
			printf/ft_power.c\
			printf/ft_precisionprint.c\
			printf/ft_printchr.c\
			printf/ft_printnum.c\
			printf/ft_printf.c\
			printf/ft_printhex.c\
			printf/ft_printhex2.c\
			printf/ft_printptrhex.c\
			printf/ft_printspace.c\
			printf/ft_printstr.c\
			printf/ft_printunsint.c\
			printf/ft_printzeros.c\

GNLSRC = gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			gnl/get_next_line_bonus.c\
			gnl/get_next_line_utils_bonus.c\

BONUSSRC = ft_lstnew.c\
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstlast.c\
			ft_lstsize.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

CC = gcc

CFLAGS = -Wextra -g3 -Wall -Ofast

DEPS = libft.h

OBJS = $(SRCS:.c=.o)

PRINTFOBJS = $(PRINTFSRC:.c=.o)

GNLOBJS = $(GNLSRC:.c=.o)

BONUSOBJ = $(BONUSSRC:.c=.o)

ALLOBJS = $(OBJS) $(BONUSOBJ) $(PRINTFOBJS) $(GNLOBJS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS) $(PRINTFOBJS) $(GNLOBJS)
	ar rcs $(NAME) $(OBJS) $(PRINTFOBJS) $(GNLOBJS)

all: $(NAME)

main.c: $(NAME)
	$(CC) $(CFLAGS) $@ $(NAME)

bonus: $(ALLOBJS)
	ar rcs $(NAME) $(ALLOBJS)

clean:
	rm -f $(OBJS) $(BONUSOBJ) $(PRINTFOBJS) $(GNLOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all