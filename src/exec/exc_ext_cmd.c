/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ext_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:33:42 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 13:39:18 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_command(t_exec *exec, char *resolved_path)
{
	int	status;

	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (exec->pid == 0)
	{
		if (execve(resolved_path, exec->argv, exec->envp) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
	{
		waitpid(exec->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		else
			g_exit_status = 1;
	}
}

static char	*resolve_path(char *command, t_env *env_list)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}
	return (resolve_command_path(command, env_list));
}

static char	**convert_env_list_to_array(t_env *env_list)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	int		count;

	i = 0;
	envp = NULL;
	tmp = env_list;
	count = get_size_env_args(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		sprintf(envp[i], "%s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	**prepare_argv(t_node *list_syntax)
{
	t_node	*arg_node;
	char	**argv;
	int		arg_count;
	int		i;

	arg_count = count_valid_args(list_syntax->next) + 1;
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		return (NULL);
	argv[0] = list_syntax->value;
	arg_node = list_syntax->next;
	i = 1;
	while (arg_node)
	{
		if (ft_strcmp("argument", arg_node->type) == 0)
		{
			argv[i++] = arg_node->value;
		}
		arg_node = arg_node->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	exec_ext_cmd(t_node *list_syntax, t_shell *shell)
{
	t_exec	*exec;
	char	*resolved_path;

	exec = init_exec();
	if (!exec)
		return ;
	g_exit_status = 0;
	exec->command = list_syntax->value;
	exec->argv = prepare_argv(list_syntax);
	exec->envp = convert_env_list_to_array(shell->env_list);
	resolved_path = resolve_path(exec->command, shell->env_list);
	if (!resolved_path)
	{
		printf("minishell: %s: Permission denied\n", exec->command);
		g_exit_status = 127;
		return ;
	}
	execute_command(exec, resolved_path);
}
