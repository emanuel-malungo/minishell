/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:24:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/07 16:24:14 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(const char *input, int *i, int *count)
{
	char	quote;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i])
			(*i)++;
		(*count)++;
	}
	else if (input[*i] == '$')
	{
		(*i)++;
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		(*count)++;
	}
	else if (check_is(input[*i], 3))
	{
		while (input[*i] && check_is(input[*i], 3))
			(*i)++;
		(*count)++;
	}
}

static int	count_word(char const *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			while (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<'))
				i++;
			count++;
		}
		else
			process_token(input, &i, &count);
	}
	return (count);
}

static t_tokenizer	*init_tokenizer(const char *input)
{
	t_tokenizer	*token;

	token = malloc(sizeof(t_tokenizer));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_tokenizer));
	token->word_count = count_word(input);
	if (token->word_count < 0)
	{
		free(token);
		return (NULL);
	}
	token->input = input;
	token->tokens = malloc((token->word_count + 1) * sizeof(char *));
	if (!token->tokens)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

int	check_is(char c, int j)
{
	if (j == 0)
		return (c == '|' || c == '>' || c == '<');
	else if (j == 1)
		return (c == '\"' || c == '\'');
	else if (j == 2)
		return (c == ' ');
	else if (j == 3)
		return (c != ' ' && c != '|' && c != '>' && c != '<' && c);
	return (0);
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
		if (!token->input[token->i])
			break ;
		if (token->input[token->i] == '\'' || token->input[token->i] == '\"')
			handle_quote_token(token);
		else if (check_is(token->input[token->i], 0))
			handle_operator_token(token);
		else if (check_is(token->input[token->i], 3))
			handle_word_token(token);
	}
	token->tokens[token->j] = NULL;
	result = token->tokens;
	free(token);
	return (result);
}
