/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:16:30 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 11:45:36 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_cd_arguments(t_node *current)
{
	int		arg_count;
	t_node	*temp;

	arg_count = 0;
	temp = current->next;
	while (temp)
	{
		if (strcmp(temp->type, "argument") == 0)
			arg_count++;
		temp = temp->next;
	}
	if (arg_count > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	return (1);
}

void	do_cd(char *path)
{
	char	*cwd;

	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		free(cwd);
		perror("Error setting PWD");
		exit(EXIT_FAILURE);
	}
	free(cwd);
}

void	ft_cd(t_node **current, t_env *env_list)
{
	char	*path;

	path = NULL;
	if (!is_valid_cd_arguments(*current))
		return ;
	if ((*current)->next && ft_strcmp((*current)->next->type, "argument") == 0)
		path = (*current)->next->value;
	else
		path = get_value_env(env_list, "HOME");
	if (!path)
	{
		printf("cd: HOME not set\n");
		exit(EXIT_FAILURE);
	}
	do_cd(path);
}
