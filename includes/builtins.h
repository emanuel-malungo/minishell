/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:27:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 16:41:59 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_node
{
	char			*type;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*value;
	char			*name;
}					t_env;

int					ft_pwd(void);
int					ft_cd(const char *path);
char				**ft_token(char const *s);
void				handle_cd(t_node **current);
int					ft_echo(t_node *syntax_list);
void				handle_command(t_node **current);
void				builtins(t_node *syntax_list);
t_node				*parse_tokens(char **tokens);
int					ft_export(void);

#endif