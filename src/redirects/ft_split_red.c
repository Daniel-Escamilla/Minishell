/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:48:18 by descamil          #+#    #+#             */
/*   Updated: 2024/09/20 23:08:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

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

static void	add_tok(char **toks, int *tok_count, const char *tok)
{
	toks[*tok_count] = ft_strdup(tok);
	(*tok_count)++;
}

static char	*extract_tok(const char *input, int *i)
{
	int		len;
	int		start;
	int		tok_len;
	char	*tok;

	len = ft_strlen(input);
	while (*i < len && ft_isspace(input[*i]))
		(*i)++;
	start = *i;
	while (*i < len && !ft_isspace(input[*i])
		&& !is_redirection(input[*i], input[*i + 1]))
		(*i)++;
	tok_len = *i - start + 1;
	tok = (char *)ft_calloc((tok_len + 1), sizeof(char));
	ft_strlcpy(tok, input + start, tok_len);
	tok[tok_len] = '\0';
	return (tok);
}

static char	*extract_redir(const char *input, int *i)
{
	char	*redir;
	int		redir_len;

	redir_len = is_redirection(input[*i], input[*i + 1]);
	redir = (char *)ft_calloc(redir_len + 1, sizeof(char));
	if (!redir)
		return (NULL);
	if (redir_len == 2)
	{
		redir[0] = input[(*i)++];
		redir[1] = input[(*i)++];
	}
	else if (redir_len == 1)
		redir[0] = input[(*i)++];
	return (redir);
}

char	**ft_split_red(const char *input, int i)
{
	char	**toks;
	char	*redir;
	char	*tok;
	int		tok_count;
	int		len;

	tok_count = 0;
	len = ft_strlen(input);
	toks = (char **)ft_calloc(sizeof(char *), (len * 2 + 1));
	if (!toks)
		return (NULL);
	while (i < len)
	{
		tok = extract_tok(input, &i);
		if (ft_strlen(tok) > 0)
			add_tok(toks, &tok_count, tok);
		free(tok);
		if (i < len && is_redirection(input[i], input[i + 1]))
		{
			redir = extract_redir(input, &i);
			add_tok(toks, &tok_count, redir);
			free(redir);
		}
	}
	return (toks);
}
