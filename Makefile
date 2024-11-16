CC = cc
SRC_DIR = src
NAME = minishell
LIBFT_DIR = libft
INCLUDE_DIR = includes
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include

CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRCS = $(SRC_DIR)/minishell.c \
       $(SRC_DIR)/builtins/builtins.c \
       $(SRC_DIR)/builtins/cd.c \
       $(SRC_DIR)/builtins/pwd.c \
       $(SRC_DIR)/builtins/echo.c \
	   $(SRC_DIR)/builtins/export.c \
       $(SRC_DIR)/parse/parse.c \
	   $(SRC_DIR)/parse/token.c 

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
