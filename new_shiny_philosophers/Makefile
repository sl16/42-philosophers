# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 09:14:33 by vbartos           #+#    #+#              #
#    Updated: 2024/01/22 18:05:33 by vbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOURS ---------------------------------- #

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

# PROJECT ---------------------------------- #

NAME			= philo

# FLAGS ------------------------------------ #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
# CFLAGS			+= -fsanitize=thread -g
RM				= rm -rf

# SOURCE FILES ----------------------------- #

SRC_PATH		= src/
SRC				= main.c\
					check_input.c\
					init.c\
					routine_philo.c\
					routine_watcher.c\
					getters_setters.c\
					utils.c\
					exit.c
					
SRCS			= $(addprefix $(SRC_PATH), $(SRC))

#SRCS_BONUS		= 

# OBJECT FILES ----------------------------- #

OBJ_PATH		= obj/
OBJ				= $(SRC:.c=.o)
OBJS			= $(addprefix $(OBJ_PATH), $(OBJ))

#OBJS_BONUS		=

# INCLUDES --------------------------------- #

INC 			= -I ./inc/

# RULES ------------------------------------ #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "$(GREEN) - Project compiled.$(RESET)"

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

clean:
	@${RM} $(OBJ_PATH)
	@echo "$(RED) - Project object files deleted.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) - Project object & binary files deleted.$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus