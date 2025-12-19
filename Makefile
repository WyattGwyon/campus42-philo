# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 18:40:58 by clouden           #+#    #+#              #
#    Updated: 2025/12/19 20:17:39 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GREEN   =	\033[0;32m
RESET   =	\033[0m  
YELLOW  =	\033[1;33m
BLUE    =	\033[0;34m

# Project Variables
CC		= 	cc
CFLAGS 	= 	-Wall -Wextra -Werror -g3 -pthread -O0#-fsanitize=address
NAME	=	philo

SRCS	= 	main.c \
			parser.c \
			init.c \
			utils.c \
			safe_utils.c \
			sim.c \
			getters_setters.c \
			sync.c \
			time.c \
			monitor.c \
			one_philo.c \

OBJS	= $(SRCS:%.c=%.o)

all:$(NAME)

$(NAME):$(OBJS)
	@printf "$(GREEN)[PHILO]$(RESET) %25s -> %s\n" $< $@
	@$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	@printf "$(BLUE)[COMPILING]$(RESET) %21s -> %s\n" $< $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|      CLEANING OBJECTS     |"
	@echo "+---------------------------+"
	@rm -rf *.o $(OBJS)

fclean: clean
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|   REMOVING EXECUTABLES    |"
	@echo "+---------------------------+"
	@rm -f $(NAME)
	@echo "$(RESET)"
	@echo "...now THAT'S effin' clean!\n"

re: fclean all

.PHONY: re all clean fclean

