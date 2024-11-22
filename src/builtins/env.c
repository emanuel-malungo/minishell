/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:30:58 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 08:04:56 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env_node *env_list)
{
	t_env_node	*current;

	if (!env_list)
	{
		perror("env: no environment variables found\n");
		return ;
	}
	current = env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		else
			printf("%s\n", current->name);
		current = current->next;
	}
}
