/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/08 13:53:25 by emalungo         ###   ########.fr       */
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

int	main(void)
{
	t_bash	*bash;
	char	*processed_input;

	bash = init_bash();
	while (1)
	{
		bash->input = readline("minishell$> ");
		if (!bash->input)
			break ;
		add_history(bash->input);
		processed_input = expand_variable(bash->input, bash);
		bash->tokens = tokenizer(processed_input);
		bash->syntax_list = parse_tokens(bash->tokens);
		exec_all_commands(bash);
		free(bash->input);
	}
	return (0);
}
