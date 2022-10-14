# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:38:52 by sharrach          #+#    #+#              #
#    Updated: 2022/07/18 18:22:42 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:	minishell

HEADER	:	minishell.h

SRCS	:	main.c
			hh.c\

OBJS	:	$(SRCS:.c=.o)

CC		:	gcc

CFLAGS	:	-Wall -Wextra -Werror

RM		:	rm -f

$(NAME)	:	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)
			make clean -C libft

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C libft

re		:	fclean all 

.phony	:	all clean fclean re