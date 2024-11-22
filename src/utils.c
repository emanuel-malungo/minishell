/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:23:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 08:41:14 by emalungo         ###   ########.fr       */
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

void free_env_list(t_env_node *env_list)
{
	t_env_node *temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}


void	fill_env_list(char **env, t_env_node **env_list)
{
	t_env_node	*new_node;
	t_env_node	*temp;
	int			i;
	char		*name;
	char		*value;
	char		*env_copy;

	*env_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env_node));
		if (!new_node)
		{
			perror("malloc failed");
			return;
		}
		env_copy = strdup(env[i]);
		if (!env_copy)
		{
			perror("strdup failed");
			free(new_node);
			return;
		}
		name = strtok(env_copy, "=");
		value = strtok(NULL, "=");
		if (name)
			new_node->name = strdup(name);
		else
			new_node->name = strdup("");
		if (value)
			new_node->value = strdup(value);
		else
			new_node->value = strdup("");
		free(env_copy);
		if (!new_node->name || !new_node->value)
		{
			perror("strdup failed");
			free(new_node->name);
			free(new_node->value);
			free(new_node);
			return;
		}

		new_node->next = NULL;

		if (*env_list == NULL)
		{
			*env_list = new_node;
		}
		else
		{
			temp = *env_list;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}

		i++;
	}
}

t_bash	*init_bash(void)
{
	t_bash	*bash;
	extern char **environ;

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
		return bash;
	}

	fill_env_list(environ, &bash->env_list);
	return bash;
}






