NAME =  PmergeMe

CPP = c++

CFLAGS = -Werror -Wall -Wextra -std=c++98

RM = rm -rf

SRCS = main.cpp PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean all

.PHONY: all clean fclean re

