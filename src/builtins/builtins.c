/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:12:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/25 09:03:58 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void handle_command(t_node **current, t_env_node *env_list)
{
    if (!current || !*current || !(*current)->value)
    {
        perror("Error: invalid node in handle_command\n");
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
        handle_export((*current)->next, &env_list);
    else if (strcmp((*current)->value, "unset") == 0)
    {
        if ((*current)->next && (*current)->next->value)
            ft_unset(&env_list, (*current)->next->value);
        else
            fprintf(stderr, "unset: not enough arguments\n");
    }
    else if (strcmp((*current)->value, "echo") == 0)
    {
        if (!ft_echo(*current))
            perror("echo");
    }
    else if (strcmp((*current)->value, "env") == 0)
        ft_env(env_list);
    else
        execute_external_command(*current, env_list);
}


void	builtins(t_node *syntax_list, t_env_node *env_list)
{
	t_node	*current;

	if (!syntax_list)
	{
		perror("Error: syntax_list is NULL\n");
		return ;
	}
	current = syntax_list;
	while (current)
	{
		if (!current->type || !current->value)
		{
			perror("Error: invalid node in syntax_list\n");
			return ;
		}
		if (ft_strcmp(current->type, "command") == 0)
			handle_command(&current, env_list);
		current = current->next;
	}
}
