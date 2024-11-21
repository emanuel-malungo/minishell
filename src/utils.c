/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:23:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:26:28 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_node *node)
{
	while (node)
	{
		printf("Node type: %s, value: %s\n", node->type, node->value);
		node = node->next;
	}
}

void	free_list(t_node *node)
{
	t_node	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->value);
		free(temp);
	}
}

t_bash	*init_bash(void)
{
	t_bash	*bash;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (NULL);
	ft_memset(bash, 0, sizeof(t_bash));
	return (bash);
}
