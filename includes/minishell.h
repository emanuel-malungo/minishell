/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:45:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <stdlib.h>
# include "./parse.h"
# include <dirent.h>
# include <unistd.h>
# include <string.h>
# include "./token.h"
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "./builtins.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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