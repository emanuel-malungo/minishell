/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:45:33 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/20 14:56:03 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	*expand_env_var(const char *input)
{
	const char	*var;

	var = getenv(input);
	if (!var)
		return (ft_strdup(""));
	return (ft_strdup(var));
}

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
