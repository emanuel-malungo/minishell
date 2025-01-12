/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:06:15 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 11:47:31 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redir(t_node *list_syntax)
{
	t_node	*current;

	current = list_syntax;
	while (current != NULL)
	{
		if (current->type && ft_strcmp(current->type, "<") == 0)
			input_redir(current);
		else if (current->type && ft_strcmp(current->type, "<<") == 0)
			heredoc_redir(current);
		else if (current->type && ft_strcmp(current->type, ">>") == 0)
			append_redir(current);
		else if (current->type && ft_strcmp(current->type, ">") == 0)
			output_redir(current);
		current = current->next;
	}
	return (1);
}
