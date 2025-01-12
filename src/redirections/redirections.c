/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:06:15 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 13:30:38 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	has_redirection(t_shell *shell)
{
	t_node	*current;

	current = shell->list_syntax;
	shell->redir_needed = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->type, "<") == 0 || ft_strcmp(current->type,
				"<<") == 0 || ft_strcmp(current->type, ">>") == 0
			|| ft_strcmp(current->type, ">") == 0 || ft_strcmp(current->type,
				"pipe") == 0)
		{
			shell->redir_needed = 1;
			break ;
		}
		current = current->next;
	}
}

static int	append_redir(t_node *current)
{
	int	fd;

	fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	output_redir(t_node *current)
{
	int	fd;

	fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	input_redir(t_node *current)
{
	int	fd;

	fd = open(current->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redir(t_node *list_syntax)
{
	t_node	*current;

	current = list_syntax;
	while (current != NULL)
	{
		if (current->type && ft_strcmp(current->type, ">") == 0)
			output_redir(current);
		else if (current->type && ft_strcmp(current->type, "<") == 0)
			input_redir(current);
		else if (current->type && ft_strcmp(current->type, ">>") == 0)
			append_redir(current);
		else if (current->type && ft_strcmp(current->type, "<<") == 0)
			heredoc_redir(current);
		current = current->next;
	}
	return (1);
}
