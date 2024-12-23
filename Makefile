NAME=computorv1
CC=c++
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=neu.cpp

# OBJ = $(subst .c,.o,$(SRC))
all : $(NAME)

$(NAME):
	$(CC) neu.cpp -o $(NAME)

neu.opp : neu.cpp
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(NAME) 

fclean:clean
	$(RM) $(NAME)
	
re:fclean all