NAME		= ft_container
TEST		= test
SRC			= _T_vector.cpp _T_pair.cpp _T_RBtree.cpp \
			  _T_map.cpp _T_set.cpp _T_stack.cpp 
OBJ			= $(SRC:.cpp=.o)
FLAGS		= -g -Wall -Wextra -Werror -std=c++98 

all			: $(NAME)

$(NAME)		: $(OBJ) main.o
			g++ $(FLAGS) -o $@ $^

$(TEST)		: $(OBJ) $(TEST).o
			g++ $(FLAGS) -o $@ $^
	
%.o			: %.cpp
			g++ $(FLAGS) -o $@ -c $^

clean		:
			rm -rf *.o

fclean		: clean
			rm -rf $(NAME) test

re			: fclean all
