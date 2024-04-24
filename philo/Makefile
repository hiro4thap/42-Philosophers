CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
#OBJ_BONUS_DIR = obj_bonus/
SRC_DIR = src/
#SRC_BONUS_DIR = src_bonus/

NAME = philo

NAME_BONUS = philo_bonus

INCS = -Iinc/

SRC = main.c \
		validation.c \
		time.c \
		init.c \
		utils.c \
		dinner.c \
		monitor.c \
		exclusive.c

#SRC_BONUS = main_bonus.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
#SRCS_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
#OBJ_BONUS = $(patsubst $(SRC_BONUS_DIR)%.c,$(OBJ_BONUS_DIR)%.o,$(SRCS_BONUS))

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(INCS) -o $@ 

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

#bonus:${NAME_BONUS}
#
#{NAME_BONUS}:$(OBJ_BONUS)
#	$(CC) $(OBJ_BONUS) $(CFLAGS) $(INCS) -o $@
#
#$(OBJ_BONUS_DIR)%.o:$(SRC_BONUS_DIR)%.c
#	mkdir -p $(OBJ_BONUS_DIR)
#	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
#	rm -rf $(OBJ_BONUS_DIR)

fclean:clean
	rm -rf $(NAME) #${NAME_BONUS}

re:fclean all

#TODO:remove before submission
debug: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(INCS) -g -o $@

.PHONY: all clean fclean re #bonus
