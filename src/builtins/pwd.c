/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:58:53 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/07 10:52:56 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_node *current, t_bash *bash)
{
	char	*cwd;

	if (current && current->next)
	{
		printf("pwd: too many arguments\n");
		bash->exit_status = 1;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		bash->exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	bash->exit_status = 0;
}
