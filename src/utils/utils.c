/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:23:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/06 06:50:06 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_node_sorted(t_env_node **head, t_env_node *new_node)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!*head || ft_strcmp(new_node->name, (*head)->name) < 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	current = *head;
	prev = NULL;
	while (current && ft_strcmp(new_node->name, current->name) > 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_node;
	new_node->next = current;
}

t_env_node	*create_env_node(char *name, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (name)
		new_node->name = ft_strdup(name);
	else
		new_node->name = ft_strdup("");
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	if (!new_node->name || !new_node->value)
	{
		perror("strdup failed");
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	fill_env_list(char **env, t_env_node **env_list)
{
	t_env_node	*new_node;
	char		*env_copy;
	char		*name;
	char		*value;
	int			i;

	*env_list = NULL;
	i = 0;
	while (env[i])
	{
		env_copy = ft_strdup(env[i]);
		if (!env_copy)
		{
			perror("strdup failed");
			return ;
		}
		name = ft_strtok(env_copy, "=");
		value = ft_strtok(NULL, "=");
		new_node = create_env_node(name, value);
		free(env_copy);
		if (!new_node)
			return ;
		add_node_sorted(env_list, new_node);
		i++;
	}
}

t_bash	*init_bash(void)
{
	t_bash		*bash;
	extern char	**environ;

	bash = malloc(sizeof(t_bash));
	if (!bash)
	{
		perror("malloc failed");
		return (NULL);
	}
	ft_memset(bash, 0, sizeof(t_bash));
	if (!environ || !*environ)
	{
		perror("Environment is empty or NULL");
		bash->env_list = NULL;
		return (bash);
	}
	fill_env_list(environ, &bash->env_list);
	return (bash);
}
