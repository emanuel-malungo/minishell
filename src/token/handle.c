/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:09:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:16:42 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token.h"

void	handle_quote_token(t_tokenizer *token)
{
	char	quote;
	int		size;

	size = 0;
	quote = token->input[token->i++];
	while (token->input[token->i] && token->input[token->i] != quote)
	{
		size++;
		token->i++;
	}
	if (token->input[token->i] != quote)
	{
		free_tokenizer(token);
		return ;
	}
	token->tokens[token->j] = malloc(size + 1);
	if (!token->tokens[token->j])
	{
		free_tokenizer(token);
		return ;
	}
	ft_strlcpy(token->tokens[token->j], &token->input[token->i - size], size + 1);
	token->tokens[token->j][size] = '\0';
	token->j++;
	token->i++;
}

void handle_env_variable(t_tokenizer *tokenizer)
{
    int var_size = 0;

    tokenizer->i++;
    while (ft_isalnum(tokenizer->input[tokenizer->i]) || tokenizer->input[tokenizer->i] == '_')
    {
        var_size++;
        tokenizer->i++;
    }
    char var[var_size + 1];
    ft_strlcpy(var, &tokenizer->input[tokenizer->i - var_size], var_size + 1);
    var[var_size] = '\0';
    char *expanded = expand_env_var(var);
    if (!expanded)
        expanded = ft_strdup("");

    tokenizer->tokens[tokenizer->j] = expanded;
    tokenizer->j++;
}

void	handle_word_token(t_tokenizer *token)
{
	int	size;

	size = wordsize(token->input, token->i);
	token->tokens[token->j] = malloc(size + 1);
	if (!token->tokens[token->j])
	{
		free_tokenizer(token);
		return ;
	}
	ft_strlcpy(token->tokens[token->j], &token->input[token->i], size + 1);
	token->tokens[token->j][size] = '\0';
	token->j++;
	token->i += size;
}

void	handle_operator_token(t_tokenizer *token)
{
	if ((token->input[token->i] == '>' || token->input[token->i] == '<')
		&& token->input[token->i] == token->input[token->i + 1])
	{
		token->tokens[token->j] = malloc(3);
		if (!token->tokens[token->j])
		{
			free_tokenizer(token);
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
			free_tokenizer(token);
			return ;
		}
		token->tokens[token->j][0] = token->input[token->i];
		token->tokens[token->j][1] = '\0';
		token->j++;
		token->i++;
	}
}
