# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smia <smia@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 05:01:40 by smia              #+#    #+#              #
#    Updated: 2022/12/30 06:32:39 by smia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = Containers

SRCS =  main.cpp\

CC = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98

RM = rm -f
LIB =	AvlTree.hpp \
		is_integral.hpp \
		pair.hpp \
		lexicographical_compare.hpp \
		iterator.hpp \
		vector.hpp \
		stack.hpp \
		map.hpp 

OBJT = $(SRCS:.cpp=.o)

$(NAME): $(OBJT) $(LIB)
	$(CC) $(OBJT) $(FLAGS) -o $(NAME)

%.o : %.cpp $(LIB)
	$(CC) $(FLAGS) -o $@ -c $<

all : $(NAME)

clean:
	$(RM) $(OBJT)

fclean:
	$(RM) $(OBJT) $(NAME)

re:	fclean all

.PHONY: all fclean clean re
