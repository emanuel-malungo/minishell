/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:16:30 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 13:28:58 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

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
