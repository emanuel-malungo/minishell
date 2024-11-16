/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:45:33 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/16 11:39:43 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// int	ft_echo(t_node *syntax_list)
// {
// 	t_node	*current;
// 	int		newline;

// 	current = syntax_list->next;
// 	newline = 1;
// 	if (current && strcmp(current->value, "-n") == 0)
// 	{
// 		newline = 0;
// 		current = current->next;
// 	}
// 	while (current)
// 	{
// 		if (current->value)
// 		{
// 			printf("%s", current->value);
// 			.if (current->next) printf(" ");
// 		}
// 		current = current->next;
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (1);
// }

int	ft_echo(t_node *syntax_list)
{
	int		line;
	t_node	*current;

	current = syntax_list->next;
	line = 1;
	if (current && strcmp(current->value, "-n") == 0)
	{
		line = 0;
		current = current->next;
	}
	while (current)
	{
		if (current->value)
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
