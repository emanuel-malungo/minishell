/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:58:07 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 02:20:40 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **environ)
{
	t_shell	*shell;

	shell = init_shell(environ);
	if (argc == 1)
	{
		while (1)
		{
			shell->input = readline("minishell$> ");
			if (!shell->input)
				break ;
			add_history(shell->input);
			if (!process_input(shell))
				return (1);
		}
		return (0);
	}
	printf("minishell: %s: No such file or directory\n", argv[1]);
	return (1);
}
