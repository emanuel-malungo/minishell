/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:22:35 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/12 12:03:40 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_size_redir(char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
	{
		if (input[*i + 1] == input[*i])
			*i += 2;
		else
			(*i)++;
	}
}

void	get_size_quote(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	if (quote == '"' || quote == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
	}
}

int	get_size_token(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			i++;
		get_size_redir(input, &i);
		if (input[i] == '"' || input[i] == '\'')
		{
			get_size_quote(input, &i);
			len++;
		}
		else
		{
			while (input[i] && input[i] != ' ' && input[i] != '|'
				&& input[i] != '>' && input[i] != '<' && input[i] != '"'
				&& input[i] != '\'')
				i++;
			len++;
		}
	}
	return (len);
}

t_token	*init_token(char *input)
{
	t_token	*token;
	int		token_size;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	token_size = get_size_token(input);
	token->tokens = malloc(sizeof(char *) * (token_size * 1));
	if (!token->tokens)
		return (NULL);
	return (token);
}

char	**tokenizer(char *input)
{
	t_token	*token;
	char	**result;

	token = init_token(input);
	if (!token)
		return (NULL);
	while (input[token->i])
	{
		while (input[token->i] == ' ')
			token->i++;
		if (input[token->i] == '\'' || input[token->i] == '"')
			handle_quoto_token(token, input);
		else if (input[token->i] == '|' || input[token->i] == '>'
			|| input[token->i] == '<')
			handle_operator_token(token, input);
		else
			handle_word_token(token, input);
	}
	token->tokens[token->j] = NULL;
	result = token->tokens;
	free(token);
	return (result);
}
