/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:00:52 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 15:26:32 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "./minishell.h"

int		ft_count_word(char const *s);
char	**ft_token(char const *s);
int		ft_isspace(const char s);
void	ft_free(char **strs, int j);
int		ft_wordsize(char const *str, int i);
char	*expand_env_var(const char *input);

#endif