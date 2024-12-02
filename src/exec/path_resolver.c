/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:15 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/02 12:56:45 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_path_env(t_env_node *env_list)
{
	t_env_node	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (strcmp(tmp->name, "PATH") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*try_resolve_command(const char *command, const char *directory)
{
	char	*command_path;

	command_path = malloc(strlen(directory) + strlen(command) + 2);
	if (!command_path)
		return (NULL);
	sprintf(command_path, "%s/%s", directory, command);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

char	*resolve_command_path(const char *command, t_env_node *env_list)
{
	char	*path_env;
	char	**directories;
	char	*command_path;
	int		i;

	path_env = find_path_env(env_list);
	if (!path_env)
		return (NULL);
	directories = ft_split(path_env, ':');
	if (!directories)
		return (NULL);
	command_path = NULL;
	i = 0;
	while (directories[i])
	{
		command_path = try_resolve_command(command, directories[i]);
		if (command_path)
			break ;
		i++;
	}
	while (directories[i])
	{
		free(directories[i]);
		i++;
	}
	free(directories);
	return (command_path);
}

char	**convert_env_list_to_array(t_env_node *env_list)
{
	int			count;
	t_env_node	*tmp;
	char		**envp;
	int			i;

	count = 0;
	tmp = env_list;
	envp = NULL;
	i = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		envp[i] = malloc(strlen(tmp->name) + strlen(tmp->value) + 2);
		if (!envp[i])
			break ;
		sprintf(envp[i], "%s=%s", tmp->name, tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
