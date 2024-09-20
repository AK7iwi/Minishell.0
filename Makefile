NAME			:= minishell

SRC_DIR			:= srcs
OBJ_DIR			:= obj

SRCS			:= main.c \
					lexer/token.c \
					lexer/handle_str/handle_str.c lexer/handle_str/extract_str.c lexer/handle_str/str_len.c \
					lexer/handle_special_char/handle_special_char.c lexer/handle_special_char/extract_special_char.c lexer/handle_special_char/special_char_len.c \
					lexer/token_utils.c \
					synthesis_analysis/analyze_tokens.c \
					synthesis_analysis/synthesis_error.c \
					synthesis_analysis/fill_cmd.c \
					synthesis_analysis/synthesis_analysis_utils.c \
					ast/ast.c \
					error/msg_error.c \
					utils/lib/lib_checker.c utils/lib/lib_len.c utils/lib/lib_memory.c utils/lib/lib_str_manip.c \
					utils/free.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CPPFLAGS    	:= -I includes
FSANITIZE_FLAG	:= -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector-strong -fno-optimize-sibling-calls 

RM				:= rm -rf
DIR_DUP     	= mkdir -p $(@D)

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;36m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)
	@echo "$(RED)Minishell objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)Minishell cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(RED)Cleaned and rebuilt!$(DEF_COLOR)"

.PHONY: all clean fclean re

# $(FSANITIZE_FLAG)