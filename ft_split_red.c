/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:48:18 by descamil          #+#    #+#             */
/*   Updated: 2024/07/23 14:56:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char c, char c1)
{
	if (c == '<' || c == '>')
	{
		if (c1 == '<' || c1 == '>')
			return (2);
		return (1);
	}
	return (0);
}

void	add_token(char **tokens, int *token_count, const char *token)
{
	tokens[*token_count] = ft_strdup(token);
	(*token_count)++;
}

char	*extract_token(const char *input, int *i)
{
	int		len;
	int		token_start;
	int		token_len;
	char	*token;

	len = ft_strlen(input);
	while (*i < len && ft_isspace(input[*i]))
		(*i)++;
	token_start = *i;
	while (*i < len && !ft_isspace(input[*i])
		&& !is_redirection(input[*i], input[*i + 1]))
		(*i)++;
	token_len = *i - token_start + 1;
	token = (char *)ft_calloc((token_len + 1), sizeof(char));
	ft_strlcpy(token, input + token_start, token_len);
	token[token_len] = '\0';
	return (token);
}

char	*extract_redirection(const char *input, int *i)
{
	char	*redirection;
	int		redir_len;

	redir_len = is_redirection(input[*i], input[*i + 1]);
	redirection = (char *)ft_calloc(redir_len + 1, sizeof(char));
	if (redirection == NULL)
		return (NULL);
	if (redir_len == 2)
	{
		redirection[0] = input[(*i)++];
		redirection[1] = input[(*i)++];
	}
	else if (redir_len == 1)
		redirection[0] = input[(*i)++];
	return (redirection);
}

char	**ft_split_red(const char *input, int i)
{
	char	*redirection;
	char	**tokens;
	char	*token;
	int		token_count;
	int		len;

	token_count = 0;
	len = ft_strlen(input);
	tokens = (char **)ft_calloc(sizeof(char *), (ft_strlen(input) * 2 + 1));
	if (!tokens)
		return (NULL);
	while (i < len)
	{
		token = extract_token(input, &i);
		if (ft_strlen(token) > 0)
			add_token(tokens, &token_count, token);
		free(token);
		if (i < len && is_redirection(input[i], input[i + 1]))
		{
			redirection = extract_redirection(input, &i);
			add_token(tokens, &token_count, redirection);
			free(redirection);
		}
	}
	return (tokens);
}
