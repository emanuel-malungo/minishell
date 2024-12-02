/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/03 08:35:00 by emalungo         ###   ########.fr       */
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

// ********************************************************** ./SRC/TOKEN

char			**tokenizer(char const *s);
int				is_word_char(char c);
int				check_is(char c, int j);
void			handle_word_token(t_tokenizer *token);
void			handle_quote_token(t_tokenizer *token);
int				wordsize(char const *str, int i);
void			handle_operator_token(t_tokenizer *token);

// ********************************************************** ./SRC/PARSE

void			ft_free(char **strs, int j);
t_node			*parse_tokens(char **tokens);
int				ft_isspace(const char s);
char			*expand_env_var(const char *input);
int				ft_count_word(char const *s);
int				ft_wordsize(char const *str, int i);

// ********************************************************** ./SRC/BUILTINS

int				ft_pwd(void);
void			handle_cd(t_node **current);
void			ft_env(t_env_node *env_list);
void			handle_exit(t_node **current);
int				ft_cd(const char *path);
int				ft_echo(t_node *syntax_list);
void			ft_unset(t_env_node **env_list, char *name);
void			exec_all_commands(t_node *syntax_list, t_env_node *env_list);
void			handle_export(t_node *current, t_env_node **env_list);
void			handle_command(t_node **current, t_env_node *env_list);
void			ft_export(t_env_node **env_list, char *name, char *value);

// ********************************************************** ./SRC/UTILS
t_bash			*init_bash(void);
void			free_list(t_node *node);
void			print_list(t_node *node);
char			*ft_strndup(const char *s, size_t n);
char			*expand_input(char *input, t_env_node *env_list);
void			fill_env_list(char **env, t_env_node **env_list);
int				ft_strcmp(char *s1, char *s2);
char			*get_env_value(const char *var, t_env_node *env_list);
char			*ft_strtoke(char *str, const char *delim, char **saveptr);

// ********************************************************** ./SRC/EXEC
char			**convert_env_list_to_array(t_env_node *env_list);
void			add_node(t_node **head, char *type, char *value);
char			*resolve_command_path(const char *command,
					t_env_node *env_list);
void			execute_external_command(t_node *command_node,
					t_env_node *env_list);

#endif