/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 07:05:30 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 13:50:03 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_node
{
	char				*type;
	char				*value;
	struct s_node		*next;
}						t_node;

// typedef struct s_env_node
// {
// 	char				*name;
// 	char				*value;
// 	struct s_env_node	*next;
// }						t_env_node;

typedef struct s_env_node
{
	char				*name;
	char				*value;
	struct s_env_node	*next;
	char				temp[4096];
	char				var[128];
	size_t				start;
	int					quote_flag;
}						t_env_node;


typedef struct s_tokenizer
{
	const char			*input;
	int					i;
	int					j;
	int					word_count;
	char				**tokens;
}						t_tokenizer;

typedef struct s_command_exec
{
	char				*command;
	char				**argv;
	char				**envp;
	pid_t				pid;
}						t_command_exec;

#endif
