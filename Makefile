NAME	=	minishell

CC		=	cc
FLAG	=	-Wall -Wextra -Werror -g3

DIRLIB	=	./libft/
FILELIB	=	libft.a
NAMELFT	=	$(addprefix $(DIRLIB), $(FILELIB))

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./include -I ./libft
HEADER 	=	include/minishell.h

# Color

DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Source
FILES	=	main quote_utils env_utils token
SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

# Add the path to the builtin folder to vpath
vpath %.c $(SRC_DIR) $(SRC_DIR)builtin $(SRC_DIR)utils $(SRC_DIR)parsing $(SRC_DIR)exec

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(DIRLIB)
	$(CC)  -L$(DIRLIB) $(FLAG) $(OBJS) $(NAMELFT) -lreadline -o $(NAME)
	@echo "$(GREEN)Minishell Compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean:
	@make clean -s -C $(DIRLIB)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo "$(MAGENTA)Minishell objects cleaned!$(DEF_COLOR)"

fclean: clean
	@make fclean -s -C $(DIRLIB)
	@rm -rf $(NAME)
	@echo "$(YELLOW)Minishell cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt!$(DEF_COLOR)"


.PHONY : all clean fclean re