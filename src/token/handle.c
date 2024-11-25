/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:09:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/25 10:38:36 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_quote_simples(t_tokenizer *token) {
    char quote = '\'';
    int start = token->i + 1;

    token->i++;
    while (token->input[token->i] && token->input[token->i] != quote)
        token->i++;
    if (!token->input[token->i]) { // Aspas não fechadas
        token->tokens[token->j] = NULL;
        return;
    }
    int size = token->i - start;
    token->tokens[token->j] = malloc(size + 1);
    if (!token->tokens[token->j])
        return;
    strncpy(token->tokens[token->j], &token->input[start], size);
    token->tokens[token->j][size] = '\0';
    token->j++;
    token->i++;
}

// void handle_quote_double(t_tokenizer *token) {
//     char quote = '\"';
//     char *expanded_token = malloc(1);
//     if (!expanded_token)
//         return;
//     expanded_token[0] = '\0';

//     token->i++;
//     while (token->input[token->i] && token->input[token->i] != quote) {
//         if (token->input[token->i] == '$') {
//             handle_env_variable(token);
//         } else {
//             int len = strlen(expanded_token);
//             expanded_token = realloc(expanded_token, len + 2);
//             if (!expanded_token)
//                 return;
//             expanded_token[len] = token->input[token->i];
//             expanded_token[len + 1] = '\0';
//         }
//         token->i++;
//     }
//     if (!token->input[token->i]) { // Aspas não fechadas
//         free(expanded_token);
//         return;
//     }
//     token->tokens[token->j++] = expanded_token;
//     token->i++;
// }

// void handle_env_variable(t_tokenizer *tokenizer)
// {
//     int var_size = 0;

//     tokenizer->i++;
//     while (ft_isalnum(tokenizer->input[tokenizer->i]) || tokenizer->input[tokenizer->i] == '_')
//     {
//         var_size++;
//         tokenizer->i++;
//     }
//     char var[var_size + 1];
//     strncpy(var, &tokenizer->input[tokenizer->i - var_size], var_size);
//     var[var_size] = '\0';
//     char *expanded = expand_env_var(var);
//     if (!expanded)
//         expanded = ft_strdup("");

//     tokenizer->tokens[tokenizer->j] = expanded;
//     tokenizer->j++;
// }

void handle_quote_double(t_tokenizer *token, t_env_node *env_list) {
    char quote = '\"';
    char *expanded_token = malloc(1);
    if (!expanded_token)
        return;
    expanded_token[0] = '\0';

    token->i++; // Pular o primeiro caractere de aspas

    while (token->input[token->i] && token->input[token->i] != quote) {
        if (token->input[token->i] == '$') {
            // Se encontrar um '$', expanda a variável de ambiente
            handle_env_variable(token, env_list);
        } else {
            int len = strlen(expanded_token);
            expanded_token = realloc(expanded_token, len + 2);
            if (!expanded_token)
                return;
            expanded_token[len] = token->input[token->i];
            expanded_token[len + 1] = '\0';
        }
        token->i++;
    }

    if (!token->input[token->i]) { // Aspas não fechadas
        free(expanded_token);
        return;
    }

    token->tokens[token->j++] = expanded_token;
    token->i++; // Pular o caractere de aspas de fechamento
}


void handle_env_variable(t_tokenizer *tokenizer, t_env_node *env_list)
{
    int var_size = 0;

    tokenizer->i++; // Pular o '$'

    // Determina o tamanho da variável (sequência de caracteres alfanuméricos ou '_')
    while (ft_isalnum(tokenizer->input[tokenizer->i]) || tokenizer->input[tokenizer->i] == '_') {
        var_size++;
        tokenizer->i++;
    }

    // Se nenhuma variável foi encontrada, simplesmente retorne
    if (var_size == 0) return;

    // Extrair o nome da variável
    char var[var_size + 1];
    strncpy(var, &tokenizer->input[tokenizer->i - var_size], var_size);
    var[var_size] = '\0';

    // Buscar a variável no env_list
    t_env_node *current = env_list;
    char *expanded = NULL;
    while (current) {
        if (strcmp(current->name, var) == 0) {
            // Se a variável for encontrada, pega o valor
            expanded = strdup(current->value);
            break;
        }
        current = current->next;
    }

    // Se não encontrar a variável, use uma string vazia
    if (!expanded) {
        expanded = ft_strdup("");
    }

    // Armazenar o valor expandido no array de tokens
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
