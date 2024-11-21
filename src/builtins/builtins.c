/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:12:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:27:38 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	handle_command(t_node **current)
{
	if (!current || !*current || !(*current)->value)
	{
		perror("Invalid node in handle_command\n");
		return ;
	}
	if (strcmp((*current)->value, "exit") == 0)
		handle_exit(current);
	else if (strcmp((*current)->value, "cd") == 0)
		handle_cd(current);
	else if (strcmp((*current)->value, "pwd") == 0)
	{
		if (!ft_pwd())
			perror("pwd");
	}
	else if (strcmp((*current)->value, "export") == 0)
	{
		if (ft_export())
			perror("export");
	}
	else if (strcmp((*current)->value, "echo") == 0)
	{
		if (!ft_echo(*current))
			perror("echo");
	}
}

void	builtins(t_node *syntax_list)
{
	t_node	*current;

	if (!syntax_list)
	{
		perror("Error: syntax_list is NULL");
		return ;
	}
	current = syntax_list;
	while (current)
	{
		if (!current->type || !current->value)
		{
			perror("Error: invalid node in syntax_list");
			return ;
		}
		if (strcmp(current->type, "command") == 0)
			handle_command(&current);
		if (!current)
			break ;
		current = current->next;
	}
}
