/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:13:25 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 12:18:42 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_redir(t_node *current)
{
	int		pipefd[2];
	char	*delimiter;
	char	*line;

	delimiter = current->next->value;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (1);
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[0]);
		return (1);
	}
	close(pipefd[0]);
	return (0);
}