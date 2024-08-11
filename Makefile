NAME		:= minishell

SRC_DIR		:= srcs
OBJ_DIR		:= obj

SRCS		:= main.c \

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			:= cc
CFLAG		:= -Wall -Wextra -Werror
CPPFLAGS    := -I includes
FSANITIZE_FLAG := -fsanitize=address -fsanitize=undefined  -fno-omit-frame-pointer -fstack-protector-strong  -fno-optimize-sibling-calls -g3

RM			:= rm -rf
DIR_DUP		= mkdir -p $(@D)

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
MAGENTA		= \033[0;95m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(FSANITIZE_FLAG) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	@echo "$(MAGENTA)Minishell objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)Minishell cleaned!$(DEF_COLOR)"

re: 
	$(MAKE) fclean
	$(MAKE) all
	@echo "$(YELLOW)Cleaned and rebuilt!$(DEF_COLOR)"

.PHONY: all clean fclean re