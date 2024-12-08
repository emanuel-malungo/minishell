/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:17 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/07 11:34:49 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_existing_variable(t_env_node *current, const char *value)
{
	free(current->value);
	current->value = ft_strdup(value);
	if (!current->value)
		perror("Error: memory allocation failed");
}

t_env_node	*create_new_variable(const char *name, const char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("Error: memory allocation failed");
		return (NULL);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->name || !new_node->value)
	{
		perror("Error: memory allocation failed");
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	insert_variable_in_order(t_env_node **env_list, t_env_node *new_node)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!*env_list || ft_strcmp(new_node->name, (*env_list)->name) < 0)
	{
		new_node->next = *env_list;
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current && ft_strcmp(new_node->name, current->name) > 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_node;
	new_node->next = current;
}

void	ft_export(t_env_node **env_list, char *name, char *value)
{
	t_env_node	*current;
	t_env_node	*new_node;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			update_existing_variable(current, value);
			return ;
		}
		current = current->next;
	}
	new_node = create_new_variable(name, value);
	if (!new_node)
		return ;
	insert_variable_in_order(env_list, new_node);
}
