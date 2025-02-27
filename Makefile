CC = cc
SRC_DIR = src
NAME = minishell
LIBFT_DIR = libft
INCLUDE_DIR = includes
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include

CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRCS = $(SRC_DIR)/minishell.c \
	   $(SRC_DIR)/utils/utils.c \
	   $(SRC_DIR)/utils/parse.c \
	   $(SRC_DIR)/utils/expand_variable.c \
	   $(SRC_DIR)/token/token.c \
	   $(SRC_DIR)/token/token_handle.c \
	   $(SRC_DIR)/token/token_utils.c \
	   $(SRC_DIR)/exec/exec.c \
	   $(SRC_DIR)/exec/exc_ext_cmd.c \
	   $(SRC_DIR)/exec/exec_utils.c \
	   $(SRC_DIR)/builtins/exit.c \
	   $(SRC_DIR)/builtins/cd.c \
	   $(SRC_DIR)/builtins/env.c \
	   $(SRC_DIR)/builtins/pwd.c \
	   $(SRC_DIR)/builtins/echo.c \
	   $(SRC_DIR)/builtins/unset.c \
	   $(SRC_DIR)/builtins/export.c \
	   $(SRC_DIR)/builtins/export_utils.c \
	   $(SRC_DIR)/redirections/redirections.c \
	   $(SRC_DIR)/redirections/heredoc.c \
	   $(SRC_DIR)/redirections/pipe.c

LIBFT = $(LIBFT_DIR)/libft.a

LDFLAGS = -lreadline -lhistory -lncurses

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(NAME)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re