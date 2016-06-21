##
## Makefile for  in /home/penava_b/perso/c++/MetaPrograming
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sat Apr 30 17:40:10 2016 penava_b
## Last update Fri Jun 17 17:37:45 2016 penava_b
##

CXX		= g++

RM =		rm -f

NAME =		meta

SRC =		RemoveTypeVaArgsT.cpp \
                RuntimeMap.cpp \
                Sequence.cpp \
		Split.cpp

OBJ =		$(SRC:.cpp=.o)

COMMON =       	-W -Wall -Wextra -Werror -I inc/

CXXFLAGS =     	$(COMMON) -I inc -std=c++14

LINKING =      	$(COMMON)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LINKING)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
