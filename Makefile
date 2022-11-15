# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 00:50:14 by estoffel          #+#    #+#              #
#    Updated: 2022/11/15 17:44:28 by estoffel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv

CC		=	c++

FLAGS	=	-Wall -Wextra -Werror -Iincl -g3 -MMD -MP -std=c++98

SRC		=	main.cpp		\

OBJ		:=	$(addprefix ./obj/,$(SRC:%.cpp=%.o))

DEP		=	$(addprefix ./obj/,$(OBJ:%.o=%.d))

RM		=	rm -rf

all: $(NAME)

-include $(DEP)

./obj/%.o: ./src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@printf "\n"
	@printf "\n"
	@echo "   🌼\033[1;97m I R C S E R V  C R E A T E D  W I T H  S U C C E S S 🌼\e[0m"
	@printf "\n"
	@echo "				x"
	@printf "\n"
	@echo "		✨	~ \033[1;97mBen Enora Liana\e[0m ~	✨"
	@printf "\n"
	@printf "\n"

clean:
	$(RM) obj/
	@printf "\n"
	@echo "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m"
	@printf "\n"

fclean:
	$(RM) obj/
	$(RM) $(NAME)
	@printf "\n"
	@echo "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m"
	@printf "\n"

re: fclean all

.PHONY: all clean fclean re