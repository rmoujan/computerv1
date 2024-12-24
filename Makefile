NAME=computor
CC=c++
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=neu.cpp\
	tools.cpp\

OBJ = $(subst .cpp,.opp,$(SRC))

all : $(NAME)

$(NAME):${OBJ}
	$(CC) $(OBJ) -o $(NAME)

%.opp : %.cpp
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ)

fclean:clean
	$(RM) $(NAME)
	
re:fclean all
