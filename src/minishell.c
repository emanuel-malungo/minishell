/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 15:21:35 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bash	*init_bash(void)
{
	t_bash	*bash;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (NULL);
	ft_memset(bash, 0, sizeof(t_bash));
	return (bash);
}

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

int	main(void)
{
	char	*input;
	char	**tokens;
	t_node	*syntax_list;

	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		add_history(input);
		tokens = ft_token(input);
		syntax_list = parse_tokens(tokens);
		print_list(syntax_list);
		builtins(syntax_list);
		free_list(syntax_list);
		free(input);
	}
	return (0);
}
