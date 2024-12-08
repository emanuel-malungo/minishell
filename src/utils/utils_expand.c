/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:00:25 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 14:31:05 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var, t_env_node *env_list)
{
	t_env_node	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, var) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char	*expand_variable(const char *input, t_bash *bash)
{
	char	*expanded;
	size_t	i = 0, j = 0;
	size_t	len = strlen(input);
	char	temp[4096];

	expanded = (char *)malloc(len * 2 + 1); // Expansão segura
	if (!expanded)
		return (NULL);
	while (i < len)
	{
		if (input[i] == '\'') // Aspas simples, ignora expansão
		{
			expanded[j++] = input[i++];
			while (i < len && input[i] != '\'')
				expanded[j++] = input[i++];
			if (i < len)
				expanded[j++] = input[i++];
		}
		else if (input[i] == '$') // Detecta variáveis
		{
			i++;
			if (input[i] == '?') // Expansão de $?
			{
				j += snprintf(temp, sizeof(temp), "%d", bash->exit_status);
				strncpy(&expanded[j - strlen(temp)], temp, strlen(temp));
				i++;
			}
			else
			{
				size_t start = i;
				while (i < len && (isalnum(input[i]) || input[i] == '_'))
					i++;
				char var[128];
				strncpy(var, &input[start], i - start);
				var[i - start] = '\0';
				const char *value = getenv(var);
				if (!value) // Busca no ambiente do minishell
					value = get_env_value(var, bash->env_list);
				if (value)
				{
					j += snprintf(temp, sizeof(temp), "%s", value);
					strncpy(&expanded[j - strlen(temp)], temp, strlen(temp));
				}
			}
		}
		else
			expanded[j++] = input[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*expanded_input(char *input, t_bash *bash)
{
	char	*expanded = expand_variable(input, bash);
	if (!expanded)
		return (NULL);
	return (expanded);
}