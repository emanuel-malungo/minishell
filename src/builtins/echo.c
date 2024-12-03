/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:45:33 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/03 08:17:54 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_node *syntax_list)
{
	int		line;
	t_node	*current;

	current = syntax_list->next;
	line = 1;
	if (current && ft_strcmp(current->value, "-n") == 0)
	{
		line = 0;
		current = current->next;
	}
	while (current)
	{
		if (current->value && ft_strcmp(current->type, "argument") == 0)
		{
			printf("%s", current->value);
			if (current->next)
				printf(" ");
		}
		current = current->next;
	}
	if (line)
		printf("\n");
	return (1);
}
