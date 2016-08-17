##
## Makefile for  in /home/penava_b/perso/c++/MetaPrograming
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sat Apr 30 17:40:10 2016 penava_b
## Last update Sun Aug 14 16:24:04 2016 penava_b
##

CXX		= g++

RM =		rm -f

NAME =		meta

SRC =		RemoveTypeVaArgsT.cpp \
                RuntimeMap.cpp \
                Sequence.cpp \
		Split.cpp \
		MergeSort.cpp

OBJ =		$(SRC:.cpp=.o)

COMMON =       	-W -Wall -Wextra -I inc/

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
