CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
SRC_DIR = src/

NAME = philo_bonus

INCS = -Iinc/

SRC = main.c \
		validation.c \
		time.c \
		init.c \
		utils.c \
		dinner.c \
		monitor.c \
		exclusive.c \
		protect.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(INCS) -o $@ 

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)

fclean:clean
	rm -rf $(NAME)

re:fclean all

#TODO:remove before submission
debug: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(INCS) -g -o $@

.PHONY: all clean fclean re
