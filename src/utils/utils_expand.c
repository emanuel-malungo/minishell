/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:00:25 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/06 13:55:14 by emalungo         ###   ########.fr       */
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

static char	*expand_variable(char *input, int *i, char *result,
		t_env_node *env_list)
{
	char	*var_name;
	char	*value;
	char	*temp;
	int		start;

	(*i)++;
	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	var_name = ft_substr(input, start, *i - start);
	value = get_env_value(var_name, env_list);
	if (!value)
		value = ft_strdup("");
	temp = ft_strjoin(result, value);
	return (temp);
}

static char	*append_literal(char *input, int *i, char *result)
{
	char	*literal;
	char	*temp;
	int		start;

	start = *i;
	while (input[*i] && input[*i] != '$')
		(*i)++;
	literal = ft_substr(input, start, *i - start);
	temp = ft_strjoin(result, literal);
	return (temp);
}

char	*expand_input(t_bash *bash)
{
	char	*result;
	char	*expanded_var;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (bash->input[i])
	{
		if (bash->input[i] == '\'')
			return (bash->input);
		if (bash->input[i] == '$')
		{
			if (bash->input[i + 1] == '?')
			{
				expanded_var = ft_itoa(bash->exit_status);
				result = ft_strjoin(result, expanded_var);
				free(expanded_var);
				i += 2;
			}
			else if (bash->input[i + 1] && bash->input[i + 1] != ' ')
				result = expand_variable(bash->input, &i, result, bash->env_list);
			else
				result = append_literal(bash->input, &i, result);
		}
		else
			result = append_literal(bash->input, &i, result);
	}
	return (result);
}
