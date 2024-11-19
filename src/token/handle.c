/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:09:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/19 10:34:01 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token.h"

void	handle_quote_token(t_tokenizer *token)
{
	char	quote;
	int		size;

	quote = token->input[token->i++];
	size = 0;
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
	strncpy(token->tokens[token->j], &token->input[token->i - size], size);
	token->tokens[token->j][size] = '\0';
	token->j++;
	token->i++;
}

// void	handle_env_variable(t_tokenizer *token)
// {
// 	int		var_size;
// 	char	var;
// 	char	*expanded;

// 	var_size = 0;
// 	token->i++;
// 	while (isalnum(token->input[token->i]) || token->input[token->i] == '_')
// 	{
// 		var_size++;
// 		token->i++;
// 	}
// 	var[var_size] = '\0';
// 	strncpy(var, &token->input[token->i - var_size], var_size);
// 	expanded = expand_env_var(var);
// 	if (!expanded)
// 		expanded = strdup("");
// 	token->tokens[token->j] = expanded;
// 	token->j++;
// }

void handle_env_variable(t_tokenizer *tokenizer)
{
    int var_size = 0;

    tokenizer->i++; // Avança para o caractere após `$`
    while (isalnum(tokenizer->input[tokenizer->i]) || tokenizer->input[tokenizer->i] == '_')
    {
        var_size++;
        tokenizer->i++;
    }

    // Copia o nome da variável
    char var[var_size + 1];
    strncpy(var, &tokenizer->input[tokenizer->i - var_size], var_size);
    var[var_size] = '\0';

    // Expande a variável de ambiente
    char *expanded = expand_env_var(var);
    if (!expanded)
        expanded = strdup("");

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
	strncpy(token->tokens[token->j], &token->input[token->i], size);
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
