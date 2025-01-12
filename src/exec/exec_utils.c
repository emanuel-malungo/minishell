/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:51:15 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 08:13:28 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->argv = NULL;
	exec->envp = NULL;
	exec->command = NULL;
	return (exec);
}

int	is_redirection(t_node *node)
{
	if (ft_strcmp(node->type, "<") == 0)
		return (0);
	if (ft_strcmp(node->type, "<<") == 0)
		return (0);
	if (ft_strcmp(node->type, ">") == 0)
		return (0);
	if (ft_strcmp(node->type, ">>") == 0)
		return (0);
	if (ft_strcmp(node->type, "|") == 0)
		return (0);
	return (1);
}

int	count_valid_args(t_node *list_syntax)
{
	int	count;

	count = 0;
	while (list_syntax)
	{
		if (list_syntax->value != NULL)
			count++;
		list_syntax = list_syntax->next;
	}
	return (count);
}

int	get_size_env_args(t_env *arg_env)
{
	int	count;

	count = 0;
	while (arg_env)
	{
		count++;
		arg_env = arg_env->next;
	}
	return (count);
}

char	*find_path_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*try_resolve_command(char *command, char *directory)
{
	char	*command_path;

	command_path = malloc(ft_strlen(directory) + ft_strlen(command) + 2);
	if (!command_path)
		return (NULL);
	sprintf(command_path, "%s/%s", directory, command);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

char	*resolve_command_path(char *command, t_env *env_list)
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
