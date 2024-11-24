/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 16:01:27 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./structs.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_bash
{
	char		*input;
	char		**tokens;
	char		**environ;
	t_env_node	*env_list;
	t_node		*syntax_list;
}				t_bash;

// ********************************************************** ./SRC/MINISHELL.C/ UTILS.C

t_bash			*init_bash(void);
void			free_list(t_node *node);
void			print_list(t_node *node);
int				ft_strcmp(char *s1, char *s2);

// ********************************************************** ./SRC/TOKEN

t_tokenizer		*init_tokenizer(char const *input);
void			ft_free(char **strs, int j);
void			free_tokenizer(t_tokenizer *tokenizer);
int				is_word_char(char c);
int				is_operator(char c);
char			**tokenizer(char const *s);
int				check_is(char c, int j);
int				count_word(const char *input);
int				wordsize(char const *str, int i);
void			handle_quote_double(t_tokenizer *token);
void			handle_quote_simples(t_tokenizer *token);
void			handle_env_variable(t_tokenizer *token);
void			handle_word_token(t_tokenizer *token);
void			handle_operator_token(t_tokenizer *token);

// ********************************************************** ./SRC/PARSE

int				ft_count_word(char const *s);
// char			**ft_token(char const *s);
int				ft_isspace(const char s);
void			ft_free(char **strs, int j);
int				ft_wordsize(char const *str, int i);
char			*expand_env_var(const char *input);

// ********************************************************** ./SRC/BUILTINS

int				ft_pwd(void);
int				ft_cd(const char *path);
// char			**ft_token(char const *s);
void			handle_cd(t_node **current);
t_node			*parse_tokens(char **tokens);
int				ft_echo(t_node *syntax_list);
void			handle_exit(t_node **current);
void			ft_unset(t_env_node **env_list, char *name);
void			ft_env(t_env_node *env_list);
void			ft_export(t_env_node **env_list, char *name, char *value);
void			handle_command(t_node **current, t_env_node *env_list);
void			builtins(t_node *syntax_list, t_env_node *env_list);
void			handle_export(t_node *current, t_env_node **env_list);

void execute_external_command(t_node *command_node, t_env_node *env_list);

#endif