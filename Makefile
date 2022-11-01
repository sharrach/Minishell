# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:38:52 by sharrach          #+#    #+#              #
#    Updated: 2022/11/01 17:23:34 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

HEADER	=	includes/minishell.h

SRCS	=	srcs/main.c\
			srcs/ft_llist_redir.c\
			srcs/ft_llist_mini.c\
			srcs/pipes_red.c\
			srcs/get_command.c\
			srcs/utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIBFT	=	libft

LIB		=	$(LIBFT)/libft.a

%.o:%.c		$(HEADER)
			$(CC) $(CFLAGS) -I/usr/include/readline/include -c $< -o $@ 

$(NAME)	:	$(LIB) $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) -lreadline -L/usr/include/readline/lib

$(LIB):
			make -C $(LIBFT)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)
			make clean -C $(LIBFT)

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C $(LIBFT)

re		:	fclean all

.PHONY	:	all clean fclean re