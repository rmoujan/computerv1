NAME=computorv1
CC=c++
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=neu.cpp


# OBJ = $(subst .c,.o,$(SRC))
# OBJBNS = $(subst .c,.o,$(SRCBNS))
# lib = ./libft/libft.a
# libobj = ./libft/*.o

all : $(NAME)

$(NAME):${SRC}
	$(CC) $(SRC) -o $(NAME)

%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ) $(OBJBNS) $(libobj)

fclean:clean
	$(RM) $(NAME) $(NAME2) $(lib)
	
re:fclean all