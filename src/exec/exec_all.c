/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:12:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/04 14:25:53 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	handle_command(t_node **current, t_env_node *env_list)
{
	if (!current || !*current || !(*current)->value)
	{
		perror("Error: invalid node in handle_command\n");
		return ;
	}
	if (strcmp((*current)->value, "exit") == 0)
		ft_exit(current);
	else if (ft_strcmp((*current)->value, "cd") == 0)
		ft_cd(current, env_list);
	else if (ft_strcmp((*current)->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp((*current)->value, "export") == 0)
		handle_export((*current)->next, &env_list);
	else if (ft_strcmp((*current)->value, "env") == 0)
		ft_env(env_list);
	else if (ft_strcmp((*current)->value, "echo") == 0)
		ft_echo(*current);
	else if (ft_strcmp((*current)->value, "unset") == 0)
	{
		if ((*current)->next && (*current)->next->value)
			ft_unset(&env_list, (*current)->next->value);
		else
			printf("unset: not enough arguments\n");
	}
	else
		execute_external_command(*current, env_list);
}

void	exec_all_commands(t_node *syntax_list, t_env_node *env_list)
{
	t_node	*temp;

	if (!syntax_list)
	{
		perror("Error: syntax_list is NULL\n");
		return ;
	}
	temp = syntax_list;
	while (temp)
	{
		if (!temp->type || !temp->value)
		{
			perror("Error: invalid node in syntax_list\n");
			return ;
		}
		if (ft_strcmp(temp->type, "command") == 0)
			handle_command(&temp, env_list);
		temp = temp->next;
	}
}
