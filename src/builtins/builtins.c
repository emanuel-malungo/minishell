/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:12:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 15:29:39 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	handle_cd(t_node **current)
{
	*current = (*current)->next;
	if (*current && strcmp((*current)->type, "argument") == 0)
	{
		if (!ft_cd((*current)->value))
			perror("cd");
	}
	else if (!ft_cd(NULL))
		perror("cd");
}

void	handle_command(t_node **current)
{
	if (strcmp((*current)->value, "exit") == 0)
		exit(0);
	else if (strcmp((*current)->value, "cd") == 0)
		handle_cd(current);
	else if (strcmp((*current)->value, "pwd") == 0)
		if (!ft_pwd())
			perror("pwd");
}

void	builtins(t_node *syntax_list)
{
	t_node	*current;

	if (!syntax_list)
	{
		perror("Error");
		return ;
	}
	current = syntax_list;
	while (current)
	{
		if (!current->type || !current->value)
		{
			perror("Error");
			return ;
		}
		if (strcmp(current->type, "command") == 0)
			handle_command(&current);
		current = current->next;
	}
}
