/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/25 08:40:17 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*new_node(char *type, char *value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	add_node(t_node **head, char *type, char *value)
{
	t_node	*new;
	t_node	*temp;

	new = new_node(type, value);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_node *parse_tokens(char **tokens)
{
    t_node *head = NULL;
    int i = 0;
    int after_pipe = 0;

    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0)
        {
            add_node(&head, "pipe", tokens[i]);
            after_pipe = 1;
        }
        else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
            add_node(&head, "output_redirect", tokens[i]);
            i++;
            if (tokens[i])
                add_node(&head, "file", tokens[i]);
            else
                add_node(&head, "error", "Missing file for output redirection");
        }
        else if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0)
        {
            add_node(&head, "input_redirect", tokens[i]);
            i++;
            if (tokens[i])
                add_node(&head, "file", tokens[i]);
            else
                add_node(&head, "error", "Missing file for input redirection");
        }
        else
        {
            if (after_pipe)
            {
                add_node(&head, "command", tokens[i]);
                after_pipe = 0;
            }
            else
            {
                if (!head || (ft_strcmp(head->type, "command") != 0
                              && ft_strcmp(head->type, "pipe") != 0))
                {
                    add_node(&head, "command", tokens[i]);
                }
                else
                {
                    add_node(&head, "argument", tokens[i]);
                }
            }
        }
        i++;
    }
    return (head);
}