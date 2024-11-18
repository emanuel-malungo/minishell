/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:24:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/18 12:29:42 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_tokenizer	*init_tokenizer(char const *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	tokenizer->input = input;
	tokenizer->i = 0;
	tokenizer->j = 0;
	tokenizer->quote_state = 0;
	tokenizer->quote_type = 0;
	tokenizer->word_count = count_word(input);
	if (tokenizer->word_count < 0)
	{
		free(tokenizer);
		return (NULL);
	}
	tokenizer->tokens = malloc((tokenizer->word_count + 1) * sizeof(char *));
	if (!tokenizer->tokens)
	{
		free(tokenizer);
		return (NULL);
	}
	return (tokenizer);
}

void	free_tokenizer(t_tokenizer *tokenizer)
{
	if (!tokenizer)
		return ;
	if (tokenizer->tokens)
		ft_free(tokenizer->tokens, tokenizer->j);
	free(tokenizer);
}

void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**tokenizer(char const *s)
{
	t_tokenizer	*token;
	char		**result;

	token = init_tokenizer(s);
	if (!token)
		return (NULL);
	while (token->input[token->i])
	{
		while (token->input[token->i] == ' ')
			token->i++;
		if (token->input[token->i] == '\"' || token->input[token->i] == '\'')
			handle_quote_token(token);
		else if (token->input[token->i] == '$')
			handle_env_variable(token);
		else if (check_is(token->input[token->i], 4))
			handle_word_token(token);
		else if (check_is(token->input[token->i], 3))
			handle_operator_token(token);
		else
			token->i++;
	}
	token->tokens[token->j] = NULL;
	result = token->tokens;
	free(token);
	return (result);
}
