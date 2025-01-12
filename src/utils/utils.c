/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:16:25 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 15:36:36 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*create_new_node_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static int	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_new_node_env(key, value);
	if (!new_node)
		return (0);
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		temp = *env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (1);
}

static int	fill_env_list(t_env **env_list, char **environ)
{
	int		i;
	char	*key;
	char	*value;
	char	*temp;

	i = 0;
	while (environ[i])
	{
		temp = ft_strdup(environ[i]);
		if (!temp)
			return (0);
		key = strtok(temp, "=");
		value = strtok(NULL, "=");
		if (!key || !value)
		{
			free(temp);
			i++;
			continue ;
		}
		add_env_node(env_list, key, value);
		free(temp);
		i++;
	}
	return (1);
}

t_shell	*init_shell(char **environ)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->input = NULL;
	g_exit_status = 0;
	shell->env_list = NULL;
	if (!fill_env_list(&shell->env_list, environ))
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}

int	process_input(t_shell *shell)
{
	shell->processed_input = expand_variable(shell);
	if (shell->processed_input == NULL
		|| ft_strlen(shell->processed_input) == 0)
	{
		return (1);
	}
	if (!shell->processed_input)
		return (0);
	free(shell->input);
	shell->tokens = tokenizer(shell->processed_input);
	shell->list_syntax = syntax_analysis(shell->tokens);
	if (!shell->list_syntax)
		return (0);
	return (1);
}
