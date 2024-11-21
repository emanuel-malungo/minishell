/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:47:53 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		bash->tokens = tokenizer(bash->input);
		bash->syntax_list = parse_tokens(bash->tokens);
		// print_list(bash->syntax_list);
		builtins(bash->syntax_list);
	}
	return (0);
}
