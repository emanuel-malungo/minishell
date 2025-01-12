/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:58:07 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 13:34:36 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_shell	*shell;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
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
			if (!exec(shell))
				return (1);
		}
		return (0);
	}
	printf("minishell: %s: No such file or directory\n", argv[1]);
	return (1);
}
