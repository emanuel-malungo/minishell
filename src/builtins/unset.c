/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:24:10 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/04 14:27:43 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_name_var(char *name)
{
	if (!name || ft_strlen(name) == 0)
	{
		perror("unset: invalid variable name\n");
		return (0);
	}
	return (1);
}

void	ft_unset(t_env_node **env_list, char *name)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (check_name_var(name))
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	printf("unset: %s not found\n", name);
}
