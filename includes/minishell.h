/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/19 10:24:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./builtins.h"
# include "./parse.h"
# include "./token.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
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
	t_env_node	*env;
	t_node		*syntax_list;
}				t_bash;

void			builtins(t_node *syntax_list);
t_bash			*init_bash(void);
void			free_list(t_node *node);
void			print_list(t_node *node);

#endif