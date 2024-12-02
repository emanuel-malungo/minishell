/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:00:25 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/02 12:17:39 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(const char *var, t_env_node *env_list)
{
	t_env_node	*current;

	current = env_list;
	while (current)
	{
		if (strcmp(current->name, var) == 0)
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

char	*expand_input(char *input, t_env_node *env_list)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			return (input);
		if (input[i] == '$' && input[i + 1] && input[i + 1] != ' ')
			result = expand_variable(input, &i, result, env_list);
		else
			result = append_literal(input, &i, result);
	}
	return (result);
}
