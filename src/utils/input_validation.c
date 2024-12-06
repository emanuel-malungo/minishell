/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:02:25 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/06 09:07:55 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes_balance(const char *input)
{
	int	single_quote_count;
	int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quote_count++;
		else if (*input == '\"')
			double_quote_count++;
		input++;
	}
	if (single_quote_count % 2 == 0 && double_quote_count % 2 == 0)
		return (1);
	return (0);
}

int	check_operator_syntax(const char *input)
{
	while (*input)
	{
		if ((*input == '>' || *input == '<') && *(input + 1) && *(input + 1) == *input)
		{
			input++;
		}
		else if (*input == '>' || *input == '<')
		{
			input++;
		}
		else
		{
			input++;
		}
	}
	return (1);
}

int	check_invalid_characters(const char *input)
{
	while (*input)
	{
		if (!isprint((unsigned char)*input) && *input != ' ' && *input != '\t' && *input != '\n')
		{
			return (1);
		}
		input++;
	}
	return (0);
}

int	check_invalid_spaces(const char *input)
{
	while (*input)
	{
		if ((*input == '>' || *input == '<' || *input == '|') && (*(input + 1) == ' ' || *(input + 1) == '\t'))
		{
			return (0);
		}
		input++;
	}
	return (1);
}

int	check_redirection_file(const char *input)
{
	while (*input)
	{
		if (*input == '>' || *input == '<')
		{
			input++;
			while (*input == ' ' || *input == '\t')
				input++;
			if (*input == '\0')
			{
				return (0);
			}
		}
		input++;
	}
	return (1);
}

int	check_pipe_syntax(const char *input)
{
	if (*input == '|' || *(input + 1) == '|')
		return (0);
	while (*input)
	{
		if (*input == '|' && (*(input + 1) == ' ' || *(input + 1) == '\0'))
		{
			return (0);
		}
		input++;
	}
	return (1);
}

int	validate_user_input(const char *input)
{
	if (!check_quotes_balance(input))
	{
		printf("Erro: aspas não balanceadas.\n");
		return (0);
	}
	if (check_invalid_characters(input))
	{
		printf("Erro: caracteres inválidos na entrada.\n");
		return (0);
	}
	if (!check_operator_syntax(input))
	{
		printf("Erro: sintaxe de operador inválida.\n");
		return (0);
	}
	if (!check_invalid_spaces(input))
	{
		printf("Erro: espaços inválidos ao redor de operadores.\n");
		return (0);
	}
	if (!check_redirection_file(input))
	{
		printf("Erro: falta de arquivo para redirecionamento.\n");
		return (0);
	}
	if (!check_pipe_syntax(input))
	{
		printf("Erro: sintaxe de pipe inválida.\n");
		return (0);
	}
	return (1);
}


