# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybensell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 11:06:19 by ybensell          #+#    #+#              #
#    Updated: 2022/01/13 09:21:53 by ybensell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = ft_strjoin.c main.c ft_split.c ft_split2.c ft_strlen.c\
	  ft_strncmp.c tools.c

OBJ = ${SRC:.c=.o}

HEADER = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME) 

re : fclean all
