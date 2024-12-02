/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/02 16:09:09 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_output_redirect(char **tokens, int *i, t_node **head)
{
	add_node(head, "output_redirect", tokens[*i]);
	(*i)++;
	if (tokens[*i])
		add_node(head, "file", tokens[*i]);
	else
		add_node(head, "error", "Missing file for output redirection");
}

static void	handle_input_redirect(char **tokens, int *i, t_node **head)
{
	add_node(head, "input_redirect", tokens[*i]);
	(*i)++;
	if (tokens[*i])
		add_node(head, "file", tokens[*i]);
	else
		add_node(head, "error", "Missing file for input redirection");
}

static void	handle_pipe(char **tokens, int *i, t_node **head, int *after_pipe)
{
	add_node(head, "pipe", tokens[*i]);
	*after_pipe = 1;
}

static void	handle_command_or_argument(char **tokens, int *i, t_node **head,
		int *after_pipe)
{
	if (*after_pipe)
	{
		add_node(head, "command", tokens[*i]);
		*after_pipe = 0;
	}
	else
	{
		if (!*head || (strcmp((*head)->type, "command") != 0
				&& strcmp((*head)->type, "pipe") != 0))
		{
			add_node(head, "command", tokens[*i]);
		}
		else
		{
			add_node(head, "argument", tokens[*i]);
		}
	}
}



t_node	*parse_tokens(char **tokens)
{
	t_node	*head;
	int		i;
	int		after_pipe;

	i = 0;
	head = NULL;
	after_pipe = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			handle_pipe(tokens, &i, &head, &after_pipe);
		else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i],
				">>") == 0)
			handle_output_redirect(tokens, &i, &head);
		else if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i],
				"<<") == 0)
			handle_input_redirect(tokens, &i, &head);
		else
			handle_command_or_argument(tokens, &i, &head, &after_pipe);
		i++;
	}
	return (head);
}
