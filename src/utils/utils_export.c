/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:30:04 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/07 11:33:01 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_all_exports(t_env_node *env_list)
{
	t_env_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
}

int	extract_name_value(char *input, char **name, char **value)
{
	char	*equal_sign;

	*name = NULL;
	*value = NULL;
	equal_sign = ft_strchr(input, '=');
	if (equal_sign)
	{
		*name = ft_strndup(input, equal_sign - input);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*name = ft_strdup(input);
		*value = NULL;
	}
	if (!*name || (equal_sign && !*value))
	{
		free(*name);
		free(*value);
		perror("Error: memory allocation failed");
		return (0);
	}
	return (1);
}

void	process_export_variable(t_env_node **env_list, char *name, char *value,
		t_bash *bash)
{
	if (!is_valid_identifier(name))
	{
		fprintf(stderr, "export: '%s': not a valid identifier\n", name);
		bash->exit_status = 1;
		free(name);
		free(value);
		return ;
	}
	ft_export(env_list, name, value ? value : "");
	free(name);
	free(value);
}

void	handle_export(t_node *current, t_env_node **env_list, t_bash *bash)
{
	char *name;
	char *value;

	bash->exit_status = 0;
	if (!current || !current->value)
	{
		print_all_exports(*env_list);
		return ;
	}
	if (!extract_name_value(current->value, &name, &value))
	{
		bash->exit_status = 1;
		return ;
	}
	process_export_variable(env_list, name, value, bash);
}