/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:55:47 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/11 15:30:04 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_quoto_token(t_token *token, char *input)
{
	int	start;
	int	len;
	int	i;

	token->quote = input[token->i];
	start = token->i + 1;
	len = 0;
	i = start;
	while (input[i] && input[i] != token->quote)
	{
		len++;
		i++;
	}
	if (input[i] == token->quote)
	{
		token->tokens[token->j] = malloc(sizeof(char) * (len + 1));
		if (!token->tokens[token->j])
			return ;
		strncpy(token->tokens[token->j], &input[start], len);
		token->tokens[token->j][len] = '\0';
		token->j++;
		token->i = i + 1;
	}
	else
		token->i = i;
}

void	handle_operator_token(t_token *token, char *input)
{
	char	*operator;
	int		operator_len;
	int		i;

	operator_len = 1;
	i = token->i;
	if ((input[i] == '|' && input[i + 1] == '|') || (input[i] == '>' && input[i
			+ 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
	{
		operator_len = 2;
	}
	operator= malloc(sizeof(char) * (operator_len + 1));
	if (!operator)
		return ;
	strncpy(operator, & input[i], operator_len);
	operator[operator_len] = '\0';
	token->tokens[token->j] = operator;
	token->j++;
	token->i = i + operator_len;
}

static int	skip_quotes(char *input, int i)
{
	char	quote;

	quote = input[i++];
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

static void	add_token(t_token *token, char *input, int start, int end)
{
	char	*word;
	char	*cleaned_word;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return ;
	strncpy(word, &input[start], end - start);
	word[end - start] = '\0';
	cleaned_word = remove_quotes(word);
	free(word);
	token->tokens[token->j++] = cleaned_word;
}

void	handle_word_token(t_token *token, char *input)
{
	int	start;
	int	i;

	i = token->i;
	while (input[i] && input[i] == ' ')
		i++;
	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>'
		&& input[i] != '<')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i);
		else
			i++;
	}
	if (i > start)
		add_token(token, input, start, i);
	token->i = i;
}
