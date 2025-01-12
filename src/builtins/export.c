/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:17 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/11 20:56:43 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	len;
	size_t	i;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len] && len < n)
		len++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = '\0';
	return (dst);
}

void	insert_variable_in_order(t_env **env_list, t_env *new_node)
{
	t_env	*current;
	t_env	*prev;

	if (!*env_list || ft_strcmp(new_node->key, (*env_list)->key) < 0)
	{
		new_node->next = *env_list;
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current && ft_strcmp(new_node->key, current->key) > 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_node;
	new_node->next = current;
}

t_env	*create_new_variable(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Error: memory allocation failed");
		return (NULL);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		perror("Error: memory allocation failed");
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_export(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				perror("Error: memory allocation failed");
			return ;
		}
		current = current->next;
	}
	new_node = create_new_variable(key, value);
	if (!new_node)
		return ;
	insert_variable_in_order(env_list, new_node);
}
