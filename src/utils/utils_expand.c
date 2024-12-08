/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:00:25 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 14:03:14 by emalungo         ###   ########.fr       */
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

char	*handle_variable(const char *input, size_t *i, size_t *j, t_bash *bash)
{
	t_env_node	*env;
	const char	*value;

	env = bash->env_list;
	env->start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	strncpy(env->var, &input[env->start], *i - env->start);
	env->var[*i - env->start] = '\0';
	value = getenv(env->var);
	if (!value)
		value = get_env_value(env->var, env);
	if (value)
		*j += snprintf(&env->temp[*j], sizeof(env->temp) - *j, "%s", value);
	return (env->temp);
}

char	*expand_variable(const char *input, t_bash *bash)
{
	t_env_node	*env;
	char		*expanded;
	size_t		i;
	size_t		j;

	env = bash->env_list;
	expanded = malloc(ft_strlen(input) * 2 + 1);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !env->quote_flag)
			env->quote_flag = 1 - env->quote_flag;
		else if (input[i] == '"' && !env->quote_flag)
			env->quote_flag = 2 - env->quote_flag;
		else if (input[i] == '$' && env->quote_flag != 1)
		{
			i++;
			expanded = handle_variable(input, &i, &j, bash);
			continue;
		}
		expanded[j++] = input[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
