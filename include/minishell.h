/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:54:50 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 13:28:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

typedef struct s_token
{
	char			quote;
	char			**tokens;
	int				i;
	int				j;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_node
{
	char			*type;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_exec
{
	char			**argv;
	char			**envp;
	char			*command;
	pid_t			pid;
}					t_exec;

typedef struct s_shell
{
	char			*input;
	char			*result;
	char			**tokens;
	t_env			*env_list;
	t_node			*list_syntax;
	int				stdin;
	int				stdout;
	char			*processed_input;
	int				redir_needed;
}					t_shell;

extern int			g_exit_status;

// ***************** UTILS *****************

t_shell				*init_shell(char **environ);
t_node				*syntax_analysis(char **tokens);
char				*expand_variable(t_shell *shell);
int					process_input(t_shell *shell);
int					ft_strcmp(char *s1, char *s2);
char				*get_value_env(t_env *env_list, char *key);

// ***************** TOKEN *****************

char				**tokenizer(char *input);
char				*remove_quotes(char *str);
void				handle_word_token(t_token *token, char *input);
void				handle_quoto_token(t_token *token, char *input);
void				handle_operator_token(t_token *token, char *input);

// ***************** EXEC *****************
t_exec				*init_exec(void);
int					exec(t_shell *shell);
void				exc_all_cmds(t_shell *shell);
char				*find_path_env(t_env *env_list);
char				**prepare_argv(t_node *list_syntax);
int					is_redirection(t_node *node);
int					get_size_env_args(t_env *arg_env);
int					count_valid_args(t_node *list_syntax);
void				exec_ext_cmd(t_node *list_syntax, t_shell *shell);
char				*try_resolve_command(char *command, char *directory);
char				*resolve_command_path(char *command, t_env *env_list);

// ***************** BUILTINS *****************

void				ft_pwd(void);
void				ft_env(t_env *env_list);
void				ft_unset(t_env **env_list, char *key);
char				*ft_strndup(const char *src, size_t n);
void				ft_exit(t_node **current);
void				ft_cd(t_node **current, t_env *env_list);
int					ft_echo(t_node *syntax_list);
void				handle_export(t_node *current, t_env **env_list);
void				ft_export(t_env **env_list, char *key, char *value);

// ***************** REDIRECTIONS *****************

void				has_redirection(t_shell *shell);
int					heredoc_redir(t_node *current);
int					handle_redir(t_node *list_syntax);

#endif