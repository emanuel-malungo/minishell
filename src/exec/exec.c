/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:22:12 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 15:45:42 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_command(t_node **current, t_shell *shell)
{
	t_node	*arg_node;

	if (!current || !*current || !(*current)->value)
	{
		perror("Error: invalid node in handle_command\n");
		return ;
	}
	if (strcmp((*current)->value, "exit") == 0)
		ft_exit(current);
	else if (ft_strcmp((*current)->value, "cd") == 0)
		ft_cd(current, shell->env_list);
	else if (ft_strcmp((*current)->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp((*current)->value, "export") == 0)
		handle_export((*current)->next, &shell->env_list);
	else if (ft_strcmp((*current)->value, "env") == 0)
		ft_env(shell->env_list);
	else if (ft_strcmp((*current)->value, "echo") == 0)
		ft_echo(*current);
	else if (ft_strcmp((*current)->value, "unset") == 0)
	{
		arg_node = (*current)->next;
		if (arg_node)
		{
			while (arg_node)
			{
				if (arg_node->value)
					ft_unset(&shell->env_list, arg_node->value);
				arg_node = arg_node->next;
			}
		}
		else
		{
			printf("unset: not enough arguments\n");
		}
	}
	else
		exec_ext_cmd(*current, shell);
}

void	exc_all_cmds(t_shell *shell)
{
	t_node	*temp;

	if (!shell->list_syntax)
	{
		perror("Error: syntax_list is NULL\n");
		return ;
	}
	temp = shell->list_syntax;
	while (temp)
	{
		if (!temp->type || !temp->value)
		{
			perror("Error: invalid node in syntax_list\n");
			return ;
		}
		if (ft_strcmp(temp->type, "command") == 0)
			handle_command(&temp, shell);
		temp = temp->next;
	}
}

int	exec(t_shell *shell)
{
	has_redirection(shell);
	if (shell->redir_needed)
	{
		shell->stdin = dup(STDIN_FILENO);
		shell->stdout = dup(STDOUT_FILENO);
		if (shell->stdin == -1 || shell->stdout == -1)
		{
			perror("dup failed");
			return (0);
		}
		handle_redir(shell->list_syntax);
	}
	exc_all_cmds(shell);
	if (shell->redir_needed)
	{
		dup2(shell->stdin, STDIN_FILENO);
		dup2(shell->stdout, STDOUT_FILENO);
		close(shell->stdin);
		close(shell->stdout);
	}
	return (1);
}