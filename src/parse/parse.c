/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/19 16:35:10 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_node	*new_node(char *type, char *value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = strdup(value);
	node->next = NULL;
	return (node);
}

void	add_node(t_node **head, char *type, char *value)
{
	t_node	*new;
	t_node	*temp;

	new = new_node(type, value);
	if (!*head)
	{
		*head = new;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

t_node	*parse_tokens(char **tokens)
{
	t_node	*head;
	int		pos;

	head = NULL;
	pos = 0;
	while (tokens[pos])
	{
		if (strcmp(tokens[pos], "|") == 0)
		{
			if (tokens[pos + 1])
				add_node(&head, "pipe", "|");
		}
		else if (strcmp(tokens[pos], ">") == 0 || strcmp(tokens[pos],
				">>") == 0)
		{
			add_node(&head, "output_redirect", tokens[pos]);
			pos++;
			if (tokens[pos])
				add_node(&head, "file", tokens[pos]);
		}
		else if (strcmp(tokens[pos], "<") == 0 || strcmp(tokens[pos],
				"<<") == 0)
		{
			add_node(&head, "input_redirect", tokens[pos]);
			pos++;
			if (tokens[pos])
				add_node(&head, "file", tokens[pos]);
		}
		else if (strcmp(tokens[pos], "1>") == 0 || strcmp(tokens[pos],
				"2>") == 0)
		{
			add_node(&head, "output_redirect", tokens[pos]);
			pos++;
			if (tokens[pos])
				add_node(&head, "file", tokens[pos]);
		}
		else if (strcmp(tokens[pos], "&&") == 0 || strcmp(tokens[pos],
				"||") == 0)
			add_node(&head, "logical_operator", tokens[pos]);
		else
		{
			if (!head || (strcmp(head->type, "command") != 0
					&& strcmp(head->type, "pipe") != 0))
				add_node(&head, "command", tokens[pos]);
			else
				add_node(&head, "argument", tokens[pos]);
		}
		pos++;
	}
	return (head);
}
