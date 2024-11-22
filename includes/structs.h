/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 07:05:30 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 07:29:13 by emalungo         ###   ########.fr       */
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

typedef struct s_env_node
{
	char				*name;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_tokenizer
{
	char const			*input;
	int					i;
	int					j;
	int					word_count;
	char				**tokens;
}						t_tokenizer;



#endif
