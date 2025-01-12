/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:45:33 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 10:25:11 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_node *syntax_list, t_shell *shell)
{
	int		line;
	t_node	*current;

	line = 1;
	shell->exit_status = 0;
	current = syntax_list->next;
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
