/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 15:14:48 by pnamnil          ###   ########.fr       */
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

static void	ft_set_minus_one(int *nb, int nb_len)
{
	int	i;

	i = 0;
	while (i < nb_len)
	{
		nb[i] = -1;
		i++ ;
	}
}

static void	ft_split_find_len(int *i, const char *s)
{
	if (s[*i] == '\''){
		*i += 1;
		while (s[*i] && s[*i] != '\'')
			*i += 1;
		if (s[*i])
			*i += 1;
	}
	else if (s[*i] == '\"'){
		*i += 1;
		while (s[*i] && s[*i] != '\"')
			*i += 1;
		if (s[*i])
			*i += 1;
	}
	else
	{
		while (s[*i] && s[*i] != ' ')
			*i += 1;
	}

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
	ft_set_minus_one (index, i);
	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++ ;
		if (s[i] && j % 2 == 0)
			index[j++] = i;
		ft_split_find_len (&i, s);
		if (j % 2 == 1)
			index[j++] = i;
	}
	return (ft_split_helper(s, index));
}

/* this code is finish in one function but use more memory
char	**ft_split(const char *s, char c)
{
	int		start;
	int		i;
	int		j;
	char	**split;

	j = 0;
	i = 0;
	start = -1;
	split = (char **) malloc (ft_strlen(s));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++ ;
		if (s[i])
			start = i;
		while (s[i] && s[i] != c)
			i++ ;
		if (start >= 0)
			split[j++] = ft_substr(s, start, i - start);
		start = -1;
	}
	split[j] = NULL;
	return (split);
}
*/
