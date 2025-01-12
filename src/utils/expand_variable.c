/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:43:18 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 13:00:32 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*get_value_env(t_env *env_list, char *key)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

static void	handle_single_quotes(t_shell *shell, size_t *i, size_t *j)
{
	size_t	len;

	len = ft_strlen(shell->input);
	shell->result[(*j)++] = shell->input[(*i)++];
	while (*i < len && shell->input[*i] != '\'')
	{
		shell->result[(*j)++] = shell->input[(*i)++];
	}
	if (*i < len && shell->input[*i] == '\'')
		shell->result[(*j)++] = shell->input[(*i)++];
	else
		ft_putstr_fd("Error: Unmatched single quote\n", STDERR_FILENO);
}

static int	handle_exit_status(t_shell *shell, size_t *j)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		return (0);
	strcpy(shell->result + (*j), exit_status_str);
	(*j) += ft_strlen(exit_status_str);
	free(exit_status_str);
	return (1);
}

static int	handle_env_variable(t_shell *shell, size_t *i, size_t *j)
{
	int		start;
	char	*key;
	char	*value;

	start = *i;
	while (shell->input[*i] && (ft_isalnum(shell->input[*i]) || shell->input[*i] == '_'))
		(*i)++;
	key = ft_substr(shell->input, start, *i - start);
	if (!key)
		return (0);
	value = get_value_env(shell->env_list, key);
	free(key);
	if (value)
	{
		size_t value_len = ft_strlen(value);
		if ((*j) + value_len >= ft_strlen(shell->result))
		{
			size_t new_size = (*j) + value_len + 1024;
			shell->result = realloc(shell->result, new_size);
			if (!shell->result)
				return (0);
		}
		strcpy(shell->result + (*j), value);
		(*j) += value_len;
	}
	return (1);
}

char	*expand_variable(t_shell *shell)
{
	size_t	i;
	size_t		j;
	size_t	alloc_size;

	i = 0;
	j = 0;
	alloc_size = ft_strlen(shell->input) + 1024;
	shell->result = malloc(sizeof(char) * alloc_size);
	if (!shell->result)
		return (NULL);
	while (shell->input[i] == ' ')
		i++;
	while (i < ft_strlen(shell->input))
	{
		if (shell->input[i] == '\'')
			handle_single_quotes(shell, &i, &j);
		else if (shell->input[i] == '$')
		{
			i++;
			if (shell->input[i] == '?')
			{
				if (!handle_exit_status(shell, &j))
					return (NULL);
				i++;
			}
			else
				if (!handle_env_variable(shell, &i, &j))
					return (NULL);
		}
		else
		{
			if (j >= alloc_size - 1)
			{
				alloc_size *= 2;
				shell->result = realloc(shell->result, alloc_size);
				if (!shell->result)
					return (NULL);
			}
			shell->result[j++] = shell->input[i++];
		}
	}
	shell->result[j] = '\0';
	return (shell->result);
}
