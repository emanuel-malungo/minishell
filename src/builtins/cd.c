/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:16:30 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:28:21 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	handle_cd(t_node **current)
{
	if (!current || !*current)
	{
		perror("Invalid node in handle_cd\n");
		return ;
	}
	*current = (*current)->next;
	if (*current && (*current)->type && strcmp((*current)->type,
			"argument") == 0)
	{
		if (!ft_cd((*current)->value))
			perror("cd");
	}
	else if (!ft_cd(NULL))
	{
		perror("cd");
		return ;
	}
}

int	ft_cd(const char *path)
{
	char	*cwd;

	if (path == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			perror("cd");
			return (0);
		}
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (0);
	}
	cwd = getcwd(NULL, 0);
	if (setenv("PWD", cwd, 1) != 0)
	{
		free(cwd);
		perror("Error setting PWD");
		return (0);
	}
	free(cwd);
	return (1);
}
