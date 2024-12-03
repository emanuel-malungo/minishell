/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:17 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/03 08:34:12 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(t_node *current, t_env_node **env_list)
{
	char		*name;
	char		*value;
	char		*equal_sign;
	t_env_node	*temp;

	if (!current || !current->value)
	{
		temp = *env_list;
		while (temp)
		{
			if (temp->value)
				printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			else
				printf("declare -x %s\n", temp->name);
			temp = temp->next;
		}
		return ;
	}
	equal_sign = ft_strchr(current->value, '=');
	if (equal_sign)
	{
		name = ft_strndup(current->value, equal_sign - current->value);
		value = ft_strdup(equal_sign + 1);
		if (!name || !value)
		{
			perror("Error: memory allocation failed");
			free(name);
			free(value);
			return ;
		}
		ft_export(env_list, name, value);
		free(name);
		free(value);
	}
	else
	{
		name = strdup(current->value);
		if (!name)
		{
			perror("Error: memory allocation failed");
			return ;
		}
		ft_export(env_list, name, "");
		free(name);
	}
}

void	ft_export(t_env_node **env_list, char *name, char *value)
{
	t_env_node	*current;
	t_env_node	*prev;
	t_env_node	*new_node;

	if (!name || ft_strlen(name) == 0)
	{
		perror("export: invalid variable name\n");
		return ;
	}
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			if (!current->value)
			{
				perror("Error: memory allocation failed");
				return ;
			}
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("Error: memory allocation failed");
		return ;
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!*env_list || ft_strcmp(name, (*env_list)->name) < 0)
	{
		new_node->next = *env_list;
		*env_list = new_node;
	}
	else
	{
		current = *env_list;
		while (current && ft_strcmp(name, current->name) > 0)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_node;
		new_node->next = current;
	}
}
