/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:26:53 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 07:23:39 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_digit(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	count_args(t_node *current)
{
	t_node	*temp;
	int		count;
	int		i;

	i = -1;
	count = 0;
	temp = current;
	while (temp)
	{
		if (strcmp(temp->type, "argument") == 0)
		{
			count++;
			while (temp->value[++i])
			{
				if (!is_digit(temp->value[i]) && !(i == 0
						&& temp->value[i] == '-'))
				{
					printf("exit: %s: numeric argument required\n",
						temp->value);
					return (-1);
				}
			}
		}
		temp = temp->next;
	}
	return (count);
}

void	handle_exit(t_node **current)
{
	int	arg_count;
	int	exit_code;

	if (!current || !(*current))
		exit(0);
	arg_count = count_args(*current);
	if (arg_count == -1)
		exit(2);
	else if (arg_count > 1)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	if (arg_count == 1 && (*current)->type && strcmp((*current)->type,
			"argument") == 0)
	{
		exit_code = atoi((*current)->value);
		exit(exit_code);
	}
	exit(0);
}
