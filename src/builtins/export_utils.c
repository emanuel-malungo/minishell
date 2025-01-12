/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:56:04 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 11:44:47 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || (!isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	process_export_variable(t_env **env_list, char *key, char *value,
		t_shell *shell)
{
	if (!is_valid_identifier(key))
	{
		printf("export: '%s': not a valid identifier\n", key);
		shell->exit_status = 1;
		free(key);
		free(value);
		return ;
	}
	if (value)
		ft_export(env_list, key, value);
	else
		ft_export(env_list, key, "");
	free(key);
	free(value);
}

int	extract_name_value(char *input, char **key, char **value)
{
	char	*equal_sign;

	*key = NULL;
	*value = NULL;
	equal_sign = ft_strchr(input, '=');
	if (equal_sign)
	{
		*key = ft_strndup(input, equal_sign - input);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
	if (!*key || (equal_sign && !*value))
	{
		free(*key);
		free(*value);
		perror("Error: memory allocation failed");
		return (0);
	}
	return (1);
}

void	print_all_exports(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

void	handle_export(t_node *current, t_env **env_list, t_shell *shell)
{
	char	*name;
	char	*value;

	shell->exit_status = 0;
	if (!current || !current->value)
	{
		print_all_exports(*env_list);
		return ;
	}
	if (!extract_name_value(current->value, &name, &value))
	{
		shell->exit_status = 1;
		return ;
	}
	process_export_variable(env_list, name, value, shell);
}
