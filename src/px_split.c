/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/02 11:00:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must end
	with a NULL pointer.
*/

#include "libft.h"

static char	**ft_is_split_error(char **sp, size_t size, int *idx)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(sp[i++]);
	free (idx);
	free (sp);
	return (NULL);
}

static char	**ft_split_helper(const char *s, int *idx)
{
	char	**sp;
	int		i;

	i = 0;
	while (idx[i] != -1)
		i++;
	sp = (char **) malloc (((i / 2) + 1) * sizeof(char *));
	if (sp)
	{
		i = 0;
		while (idx[i] != -1)
		{
			sp[i / 2] = ft_substr(s, idx[i], idx[i + 1] - idx[i]);
			if (sp[i / 2] == NULL)
				return (ft_is_split_error (sp, (i / 2) + 1, idx));
			i += 2;
		}
		sp[i / 2] = NULL;
	}
	else
		sp = NULL;
	free (idx);
	return (sp);
}

static void	ft_split_find_len_h(int *i, const char *s, int *index, int *j)
{
	while (s[*i] && s[*i] != ' ')
		*i += 1;
	index[*j] = *i;
	*j += 1;
}

static void	ft_split_find_len(int *i, const char *s, int *index, int *j)
{
	if (s[*i] == '\'')
	{
		*i += 1;
		index[*j - 1] = *i;
		while (s[*i] && s[*i] != '\'')
			*i += 1;
		if (s[*i])
			index[(*j)++] = (*i)++;
		else
			index[(*j)++] = (*i);
	}
	else if (s[*i] == '\"')
	{
		*i += 1;
		index[*j - 1] = *i;
		while (s[*i] && s[*i] != '\"')
			*i += 1;
		if (s[*i])
			index[(*j)++] = (*i)++;
		else
			index[(*j)++] = (*i);
	}
	else
		ft_split_find_len_h (i, s, index, j);
}

/* size of index if strlen == 1 , it require 3 for 2 index and -1 terminate */
char	**px_split(const char *s, char c)
{
	int		i;
	int		j;
	int		*index;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s) * 2 + 1;
	index = (int *) malloc (i * sizeof(int));
	if (!index)
		return (NULL);
	j = -1;
	while (++j < i)
		index[j] = -1;
	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++ ;
		if (s[i] && j % 2 == 0)
			index[j++] = i;
		ft_split_find_len (&i, s, index, &j);
	}
	return (ft_split_helper(s, index));
}
