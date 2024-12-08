/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:39 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 13:12:52 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_node *arg_node)
{
	int	count;

	count = 0;
	while (arg_node)
	{
		count++;
		arg_node = arg_node->next;
	}
	return (count);
}

static char	**prepare_argv(t_node *command_node)
{
	t_node	*arg_node;
	char	**argv;
	int		arg_count;
	int		i;

	arg_count = count_args(command_node->next);
	argv = malloc(sizeof(char *) * (arg_count + 2));
	if (!argv)
		return (NULL);
	argv[0] = command_node->value;
	arg_node = command_node->next;
	i = 1;
	while (arg_node)
	{
		argv[i] = arg_node->value;
		arg_node = arg_node->next;
		i++;
	}
	argv[arg_count + 1] = NULL;
	return (argv);
}

static char	*resolve_path(char *command, t_env_node *env_list)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}
	return (resolve_command_path(command, env_list));
}

static void	execute_command(t_command_exec *exec_data, char *resolved_path,
		t_bash *bash)
{
	int status;

	exec_data->pid = fork();
	if (exec_data->pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (exec_data->pid == 0)
	{
		if (execve(resolved_path, exec_data->argv, exec_data->envp) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
	{
		waitpid(exec_data->pid, &status, 0);
		if (WIFEXITED(status))
			bash->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			bash->exit_status = 128 + WTERMSIG(status);
		else
			bash->exit_status = 1;
	}
}

void	execute_external_command(t_node *command_node, t_bash *bash)
{
	t_command_exec	exec_data;
	char			*resolved_path;

	bash->exit_status = 0;
	exec_data.command = command_node->value;
	exec_data.argv = prepare_argv(command_node);
	if (!exec_data.argv)
	{
		bash->exit_status = 1;
		return ;
	}
	exec_data.envp = convert_env_list_to_array(bash->env_list);
	if (!exec_data.envp)
	{
		free(exec_data.argv);
		bash->exit_status = 1;
		return ;
	}
	resolved_path = resolve_path(exec_data.command, bash->env_list);
	if (!resolved_path)
	{
		bash->exit_status = 127;
		printf("%s: Command not found\n", exec_data.command);
		free(exec_data.argv);
		free(exec_data.envp);
		return ;
	}
	execute_command(&exec_data, resolved_path, bash);
	free(exec_data.argv);
	free(exec_data.envp);
	if (resolved_path != exec_data.command)
		free(resolved_path);
}
