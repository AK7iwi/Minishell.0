NAME			:= minishell

SRC_DIR			:= srcs
OBJ_DIR			:= obj

SRCS			:= main.c \
					parser/lexer/tokenizer.c \
					parser/lexer/handle_str/handle_str.c parser/lexer/handle_str/extract_str.c parser/lexer/handle_str/str_len.c \
					parser/lexer/handle_special_char/handle_special_char.c parser/lexer/handle_special_char/extract_special_char.c parser/lexer/handle_special_char/special_char_len.c \
					parser/lexer/token_utils.c \
					parser/syn_analyzer/syn_analyzer.c parser/syn_analyzer/syn_checker.c \
					parser/ast/ast.c parser/ast/ast_print.c parser/ast/ast_free.c \
					parser/ast/create_ast_node/cmd_node.c parser/ast/create_ast_node/operator_node.c parser/ast/create_ast_node/subsh_node.c \
					parser/parser_utils/parser_checker.c parser/parser_utils/parser_checker2.c \
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
	$(CC) $(OBJS)  -lreadline -o $(NAME)

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

# $(FSANITIZE_FLAG
