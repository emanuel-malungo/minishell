/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:57:50 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/21 08:21:12 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "./minishell.h"

typedef struct s_tokenizer
{
	char const	*input;
	int			i;
	int			j;
	int			word_count;
	char		**tokens;
}				t_tokenizer;

t_tokenizer		*init_tokenizer(char const *input);
void			ft_free(char **strs, int j);
void			free_tokenizer(t_tokenizer *tokenizer);
int				is_word_char(char c);
int				is_operator(char c);
char			**tokenizer(char const *s);
int				check_is(char c, int j);
int				count_word(const char *input);
int				wordsize(char const *str, int i);
void			handle_quote_double(t_tokenizer *token);
void			handle_quote_token(t_tokenizer *token);
void			handle_env_variable(t_tokenizer *token);
void			handle_word_token(t_tokenizer *token);
void			handle_operator_token(t_tokenizer *token);

#endif
