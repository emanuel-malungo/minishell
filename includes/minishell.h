/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 14:23:58 by emalungo         ###   ########.fr       */
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
	int			exit_status;
	t_node		*syntax_list;
}				t_bash;

// ********************************************************** ./SRC/TOKEN
int				check_is(char c, int j);
char			**tokenizer(char const *s);
void			handle_word_token(t_tokenizer *token);
void			handle_quote_token(t_tokenizer *token);
void			handle_operator_token(t_tokenizer *token);

// ********************************************************** ./SRC/PARSE
void			ft_free(char **strs, int j);
t_node			*parse_tokens(char **tokens);
int				ft_count_word(char const *s);
char			*expand_env_var(const char *input);
int				ft_wordsize(char const *str, int i);

// ********************************************************** ./SRC/BUILTINS
void			ft_pwd(t_bash *bash);
void			ft_exit(t_node **current, t_bash *bash);
void			ft_cd(t_node **current, t_env_node *env_list);
int				ft_echo(t_node *syntax_list, t_bash *bash);
void			ft_env(t_env_node *env_list);
void			ft_unset(t_env_node **env_list, char *name);
void			handle_export(t_node *current, t_env_node **env_list,
					t_bash *bash);
void			handle_command(t_node **current, t_bash *bash);
void			ft_export(t_env_node **env_list, char *name, char *value);
void			exec_all_commands(t_bash *bash);

// ********************************************************** ./SRC/UTILS
t_bash			*init_bash(void);
void			free_list(t_node *node);
void			print_list(t_node *node);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strndup(const char *s, size_t n);
t_env_node		*new_env_node(char *name, char *value);
char			*ft_strtok(char *str, const char *delim);
// char			*expand_input(t_bash *bah);
char	*expanded_input(char *input, t_bash *bash);
void			fill_env_list(char **env, t_env_node **env_list);
void			add_env_node(t_env_node **env_list, t_env_node *new_node);
char			*get_env_value(char *var, t_env_node *env_list);
void			handle_export(t_node *current, t_env_node **env_list,
					t_bash *bash);

// ********************************************************** ./SRC/EXEC
char			*resolve_command_path(const char *command,
					t_env_node *env_list);
void			execute_external_command(t_node *command_node, t_bash *bash);
void			add_node(t_node **head, char *type, char *value);
char			**convert_env_list_to_array(t_env_node *env_list);

#endif