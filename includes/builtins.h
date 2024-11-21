/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:27:36 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:47:25 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_node
{
	char			*type;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_env_node
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env_node;

# include "./minishell.h"

int					ft_pwd(void);
int					ft_export(void);
int					ft_cd(const char *path);
char				**ft_token(char const *s);
void				handle_cd(t_node **current);
t_node				*parse_tokens(char **tokens);
int					ft_echo(t_node *syntax_list);
void				builtins(t_node *syntax_list);
void				handle_exit(t_node **current);
void				handle_command(t_node **current);

#endif