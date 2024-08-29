# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 21:39:32 by ayhamdou          #+#    #+#              #
#    Updated: 2024/08/29 12:25:22 by ayhamdou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror

SRC = utils/utils.c utils/ft_split.c
OBJS = $(SRC:%.c=%.o)
MAIN = philo.c

all : $(NAME)
	@echo "compiled"

$(NAME) : $(OBJS) $(MAIN)
	$(CC) $(FLAGS) $(OBJS) $(MAIN) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : clean