NAME = pipex

NAME_B = pipex_bonus

CC = gcc

SRC = ft_split.c ft_splity.c pipex.c utils.c

SRC_B = uti.c ft_split.c ft_splity.c pipex_bonus.c utils.c get_next_line.c get_next_line_utils.c

OBJ_B = $(SRC_B:.c=.o)

OBJ = ${SRC:.c=.o}

all : $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) -Wall -Wextra -Werror $(OBJ_B) -o $(NAME_B)

$(NAME): $(OBJ)
	$(CC) -Wall -Wextra -Werror $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) $(OBJ_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all bonus

.PHONY: all clean fclean re bonus

