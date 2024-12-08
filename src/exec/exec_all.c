/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:12:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/07 11:20:18 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	handle_command(t_node **current, t_bash *bash)
{
	if (!current || !*current || !(*current)->value)
	{
		perror("Error: invalid node in handle_command\n");
		return ;
	}
	if (strcmp((*current)->value, "exit") == 0)
		ft_exit(current, bash);
	else if (ft_strcmp((*current)->value, "cd") == 0)
		ft_cd(current, bash->env_list);
	else if (ft_strcmp((*current)->value, "pwd") == 0)
		ft_pwd(bash);
	else if (ft_strcmp((*current)->value, "export") == 0)
		handle_export((*current)->next, &bash->env_list, bash);
	else if (ft_strcmp((*current)->value, "env") == 0)
		ft_env(bash->env_list);
	else if (ft_strcmp((*current)->value, "echo") == 0)
		ft_echo(*current, bash);
	else if (ft_strcmp((*current)->value, "unset") == 0)
	{
		if ((*current)->next && (*current)->next->value)
			ft_unset(&bash->env_list, (*current)->next->value);
		else
			printf("unset: not enough arguments\n");
	}
	else
		execute_external_command(*current, bash);
}

void	exec_all_commands(t_bash *bash)
{
	t_node	*temp;

	if (!bash->syntax_list)
	{
		perror("Error: syntax_list is NULL\n");
		return ;
	}
	temp = bash->syntax_list;
	while (temp)
	{
		if (!temp->type || !temp->value)
		{
			perror("Error: invalid node in syntax_list\n");
			return ;
		}
		if (ft_strcmp(temp->type, "command") == 0)
			handle_command(&temp, bash);
		temp = temp->next;
	}
}
