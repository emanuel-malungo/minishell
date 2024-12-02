/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:09:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/02 12:33:52 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote_token(t_tokenizer *token)
{
	char	quote;
	int		start;
	int		size;

	quote = token->input[token->i];
	start = ++token->i;
	while (token->input[token->i] && token->input[token->i] != quote)
		token->i++;
	if (token->input[token->i] != quote)
	{
		ft_putstr_fd("Error: unmatched quotes\n", 2);
		return ;
	}
	size = token->i - start;
	token->tokens[token->j] = malloc(size + 1);
	ft_strlcpy(token->tokens[token->j], &token->input[start], size + 1);
	token->tokens[token->j][size] = '\0';
	token->j++;
	token->i++;
}

void	handle_word_token(t_tokenizer *token)
{
	int	start;
	int	size;

	start = token->i;
	while (token->input[token->i] && token->input[token->i] != ' ' && token->input[token->i] != '"' && token->input[token->i] != '\'')
		token->i++;
	size = token->i - start;
	token->tokens[token->j] = malloc(size + 1);
	if (!token->tokens[token->j])
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	ft_strlcpy(token->tokens[token->j], &token->input[start], size + 1);
	token->tokens[token->j][size] = '\0';
	token->j++;
}

void	handle_operator_token(t_tokenizer *token)
{
	if ((token->input[token->i] == '>' || token->input[token->i] == '<')
		&& token->input[token->i] == token->input[token->i + 1])
	{
		token->tokens[token->j] = malloc(3);
		if (!token->tokens[token->j])
		{
			return ;
		}
		token->tokens[token->j][0] = token->input[token->i];
		token->tokens[token->j][1] = token->input[token->i];
		token->tokens[token->j][2] = '\0';
		token->j++;
		token->i += 2;
	}
	else
	{
		token->tokens[token->j] = malloc(2);
		if (!token->tokens[token->j])
		{
			return ;
		}
		token->tokens[token->j][0] = token->input[token->i];
		token->tokens[token->j][1] = '\0';
		token->j++;
		token->i++;
	}
}
