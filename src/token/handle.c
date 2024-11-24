/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:09:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/24 14:10:36 by emalungo         ###   ########.fr       */
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


// void	handle_quote_simples(t_tokenizer *token)
// {
// 	char	quote;
// 	int		size;

// 	size = 0;
// 	quote = token->input[token->i++];
// 	while (token->input[token->i] && token->input[token->i] != quote)
// 	{
// 		size++;
// 		token->i++;
// 	}
// 	if (token->input[token->i] != quote)
// 	{
// 		free_tokenizer(token);
// 		return ;
// 	}
// 	token->tokens[token->j] = malloc(size + 1);
// 	if (!token->tokens[token->j])
// 	{
// 		free_tokenizer(token);
// 		return ;
// 	}
// 	strncpy(token->tokens[token->j], &token->input[token->i - size], size);
// 	token->tokens[token->j][size] = '\0';
// 	token->j++;
// 	token->i++;
// }

void handle_quote_double(t_tokenizer *token) {
    char quote = '\"';
    char *expanded_token = malloc(1);
    if (!expanded_token)
        return;
    expanded_token[0] = '\0';

    token->i++;
    while (token->input[token->i] && token->input[token->i] != quote) {
        if (token->input[token->i] == '$') {
            handle_env_variable(token); // Expande variável e adiciona ao token
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
    token->i++;
}



// void handle_quote_double(t_tokenizer *token)
// {
//     char quote = '\"';
//     int size = 0;
//     char *expanded;
//     int i = token->i;

//     while (token->input[i] && token->input[i] != quote)
//     {
//         if (token->input[i] == '$' && token->input[i + 1] != '\"')
//         {
//             i++;
            
//             int var_len = 0;
//             while (isalnum(token->input[i + var_len]) || token->input[i + var_len] == '_')
//                 var_len++;

//             if (var_len > 0)
//             {
//                 char *env_var = malloc(var_len + 1);
//                 if (!env_var)
//                     return;
//                 strncpy(env_var, &token->input[i], var_len);
//                 env_var[var_len] = '\0';
//                 expanded = expand_env_var(env_var);
//                 free(env_var);

//                 if (!expanded)
//                     expanded = ft_strdup(""); 
//                 char *new_token = realloc(token->tokens[token->j], size + strlen(expanded) + 1);
//                 if (!new_token)
//                 {
//                     free(expanded);
//                     return; 
//                 }
//                 token->tokens[token->j] = new_token;
//                 strcat(token->tokens[token->j], expanded);
//                 size += strlen(expanded);
//                 free(expanded);

//                 i += var_len - 1;
//             }
//         }
//         else
//         {
//             size++;
//             i++;
//         }
//     }
//     if (token->input[i] != quote)
//     {
//         free_tokenizer(token);
//         return;
//     }
//     token->i = i + 1; 
// }

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
    strncpy(var, &tokenizer->input[tokenizer->i - var_size], var_size);
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
