/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:16:25 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 11:31:13 by emalungo         ###   ########.fr       */
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
	shell->exit_status = 0;
	shell->env_list = NULL;
	if (!fill_env_list(&shell->env_list, environ))
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	while (tokens[i])
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		i++;
	}
}

void	print_list(t_node *node)
{
	while (node)
	{
		printf("Node type: %s, value: %s\n", node->type, node->value);
		node = node->next;
	}
}

void	has_redirection(t_shell *shell)
{
	t_node	*current;

	current = shell->list_syntax;
	shell->redir_needed = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->type, "<") == 0 || ft_strcmp(current->type,
				"<<") == 0 || ft_strcmp(current->type, ">>") == 0
			|| ft_strcmp(current->type, ">") == 0 || ft_strcmp(current->type,
				"pipe") == 0)
		{
			shell->redir_needed = 1;
			break ;
		}
		current = current->next;
	}
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
	has_redirection(shell);
	if (shell->redir_needed)
	{
		shell->stdin = dup(STDIN_FILENO);
		shell->stdout = dup(STDOUT_FILENO);
		if (shell->stdin == -1 || shell->stdout == -1)
		{
			perror("dup failed");
			return (0);
		}
		handle_redir(shell->list_syntax);
	}
	exc_all_cmds(shell);
	if (shell->redir_needed)
	{
		dup2(shell->stdin, STDIN_FILENO);
		dup2(shell->stdout, STDOUT_FILENO);
		close(shell->stdin);
		close(shell->stdout);
	}
	return (1);
}
