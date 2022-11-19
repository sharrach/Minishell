# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:38:52 by sharrach          #+#    #+#              #
#    Updated: 2022/11/19 13:05:51 by sharrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

HEADER	=	includes/minishell.h

SRCS	=	srcs/main.c\
			srcs/pipes_red.c\
			srcs/linked_list_func/ft_llist_mini.c\
			srcs//linked_list_func/ft_llist_redir.c\
			srcs//linked_list_func/ft_lst_env.c\
			srcs//get_next_line/get_next_line.c\
			srcs//get_next_line/get_next_line_utils.c\
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
			srcs/ft_heredoc.c\
			srcs/ft_expand.c\
			srcs/utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIBFT	=	libft

LIB		=	$(LIBFT)/libft.a

%.o:%.c		$(HEADER)
			$(CC) $(CFLAGS) -I/Users/$(USER)/.brew/opt/readline/include -c $< -o $@ 

$(NAME)	:	$(LIB) $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

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