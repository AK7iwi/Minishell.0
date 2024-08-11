NAME	=	minishell

CC		=	cc
FLAG	=	-Wall -Wextra -Werror -g3 -fsanitize=address -fsanitize=undefined  -fno-omit-frame-pointer -fstack-protector-strong  -fno-optimize-sibling-calls

SRC_DIR	=	srcs/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./include
HEADER 	=	include/minishell.h

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
MAGENTA		= \033[0;95m

# Source
FILES	=	main parsing/token
SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

# Add the path to the builtin folder to vpath
vpath %.c $(SRC_DIR) $(SRC_DIR)builtin $(SRC_DIR)utils $(SRC_DIR)parsing $(SRC_DIR)exec

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAG) $(OBJS) -lreadline -o $(NAME)
	@echo "$(GREEN)Minishell Compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo "$(MAGENTA)Minishell objects cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Minishell cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(YELLOW)Cleaned and rebuilt!$(DEF_COLOR)"


.PHONY : all clean fclean re