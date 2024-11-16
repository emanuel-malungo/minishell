/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/16 11:42:56 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_node *node)
{
	while (node)
	{
		printf("Node type: %s, value: %s\n", node->type, node->value);
		node = node->next;
	}
}

void	free_list(t_node *node)
{
	t_node	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->value);
		free(temp);
	}
}

t_bash	*init_bash(void)
{
	t_bash	*bash;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (NULL);
	ft_memset(bash, 0, sizeof(t_bash));
	return (bash);
}

int	main(void)
{
	t_bash	*bash;

	bash = init_bash();
	while (1)
	{
		bash->input = readline("minishell$> ");
		if (!bash->input)
			break ;
		add_history(bash->input);
		bash->tokens = ft_token(bash->input);
		bash->syntax_list = parse_tokens(bash->tokens);
		print_list(bash->syntax_list);
		builtins(bash->syntax_list);
		free_list(bash->syntax_list);
		free(bash->input);
	}
	return (0);
}
