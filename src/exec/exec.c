/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:22:12 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/11 20:39:40 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_command(t_node **current, t_shell *shell)
{
	if (!current || !*current || !(*current)->value)
	{
		perror("Error: invalid node in handle_command\n");
		return ;
	}
	if (strcmp((*current)->value, "exit") == 0)
		ft_exit(current, shell);
	else if (ft_strcmp((*current)->value, "cd") == 0)
		ft_cd(current, shell->env_list);
	else if (ft_strcmp((*current)->value, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp((*current)->value, "export") == 0)
		handle_export((*current)->next, &shell->env_list, shell);
	else if (ft_strcmp((*current)->value, "env") == 0)
		ft_env(shell->env_list);
	else if (ft_strcmp((*current)->value, "echo") == 0)
		ft_echo(*current, shell);
	else if (ft_strcmp((*current)->value, "unset") == 0)
	{
		if ((*current)->next && (*current)->next->value)
			ft_unset(&shell->env_list, (*current)->next->value);
		else
			printf("unset: not enough arguments\n");
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
