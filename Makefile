# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:38:52 by sharrach          #+#    #+#              #
#    Updated: 2022/11/14 22:15:48 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

HEADER	=	includes/minishell.h

SRCS	=	srcs/main.c\
			srcs/pipes_red.c\
			srcs/ft_llist_mini.c\
			srcs/ft_llist_redir.c\
			srcs/ft_lst_env.c\
			srcs/ft_tokenization.c\
			srcs/ft_parsing.c\
			srcs/ft_get_command.c\
			srcs/ft_exec_command.c\
			srcs/ft_env_dup.c\
			srcs/ft_env.c\
			srcs/ft_cd.c\
			srcs/ft_pwd.c\
			srcs/ft_unset.c\
			srcs/ft_echo.c\
			srcs/ft_export.c\
			srcs/ft_exit.c\
			srcs/ft_getsetenv.c\
			srcs/utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

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