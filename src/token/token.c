/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:24:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/25 10:34:25 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

void	free_tokenizer(t_tokenizer *token)
{
	if (!token)
		return ;
	if (token->tokens)
		ft_free(token->tokens, token->j);
	free(token);
}

t_tokenizer	*init_tokenizer(char const *input)
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

char **tokenizer(char const *s, t_env_node *env_list) {
    t_tokenizer *token;
    char **result;

    token = init_tokenizer(s);
    while (token->input[token->i]) {
        while (token->input[token->i] == ' ') // Ignorar espaços
            token->i++;
        if (!token->input[token->i]) // Se fim da entrada, sair
            break;
        if (token->input[token->i] == '\'') // Aspas simples
            handle_quote_simples(token);
        else if (token->input[token->i] == '\"') // Aspas duplas
            handle_quote_double(token, env_list);
        else if (token->input[token->i] == '$') // Variáveis de ambiente
            handle_env_variable(token, env_list);
        else if (check_is(token->input[token->i], 3)) // Palavra
            handle_word_token(token);
        else if (check_is(token->input[token->i], 0)) // Operador
            handle_operator_token(token);
        else
            token->i++;
    }
    token->tokens[token->j] = NULL;
    result = token->tokens;
    return result;
}
