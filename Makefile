NAME=computorv1
CC=c++
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=neu.cpp

all : $(NAME)

$(NAME):
	$(CC) neu.cpp -o $(NAME)

neu.o : neu.cpp
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(NAME) 

fclean:clean
	$(RM) $(NAME)
	
re:fclean all