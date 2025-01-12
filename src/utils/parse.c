/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:06:22 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 11:16:38 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_node	*new_node(char *type, char *value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = ft_strdup(type);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

static void	add_node(t_node **head, char *type, char *value)
{
	t_node	*new;
	t_node	*temp;

	new = new_node(type, value);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static void	handle_cmd_or_arg_parse(char **tokens, t_node **head, int *i,
		int *after_pipe)
{
	if (*after_pipe)
	{
		add_node(head, "command", tokens[*i]);
		*after_pipe = 0;
	}
	else
	{
		if (!*head || (ft_strcmp((*head)->type, "command") != 0
				&& ft_strcmp((*head)->type, "pipe") != 0))
		{
			add_node(head, "command", tokens[*i]);
		}
		else
			add_node(head, "argument", tokens[*i]);
	}
	(*i)++;
}

static int	handle_redir_parse(char **tokens, t_node **head, int *i, int *file)
{
	if (ft_strcmp(tokens[*i], ">") == 0 || ft_strcmp(tokens[*i], ">>") == 0)
	{
		if (ft_strcmp(tokens[*i], ">>") == 0)
			add_node(head, ">>", tokens[*i]);
		else
			add_node(head, ">", tokens[*i]);
		(*i)++;
		if (tokens[*i])
		{
			add_node(head, "file", tokens[*i]);
			*file = 1;
		}
		else
			return (0);
	}
	if (ft_strcmp(tokens[*i], "<") == 0 || ft_strcmp(tokens[*i], "<<") == 0)
	{
		if (ft_strcmp(tokens[*i], "<<") == 0)
			add_node(head, "<<", tokens[*i]);
		else
			add_node(head, "<", tokens[*i]);
		(*i)++;
		if (tokens[*i])
		{
			add_node(head, "file", tokens[*i]);
			*file = 1;
		}
		else
			return (0);
	}
	return (1);
}

t_node	*syntax_analysis(char **tokens)
{
	int		i;
	int		after_pipe;
	t_node	*head;
	int		file;

	i = 0;
	after_pipe = 0;
	head = NULL;
	file = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			add_node(&head, "pipe", tokens[i]);
			after_pipe = 1;
			i++;
		}
		else if (!handle_redir_parse(tokens, &head, &i, &file))
			return (NULL);
		else if (file != 1)
			handle_cmd_or_arg_parse(tokens, &head, &i, &after_pipe);
		else
		{
			i++;
			file = 0;
		}
	}
	return (head);
}
