/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:51:33 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 17:43:52 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	mk_free(char **result, int a)
{
	int	n;

	n = 0;
	while (n < a)
	{
		free(result[n]);
		n++;
	}
	free(result);
}

static int	mk_word(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			n++;
			i++;
		}
		else if (s[i] != '\0' && s[i] != c)
		{
			n++;
			while (s[i] != '\0' && s[i] != c)
				i++;
			if (s[i])
				i++;
		}
	}
	return (n);
}

static char	*mk_strpush(const char *s, char c, int *n)
{
	int		i;
	int		g;
	char	*tab;
	int		len;

	g = 0;
	i = *n;
	if (s[i] == c)
		i++;
	else
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (s[i] == c)
			i++;
	}
	len = i - *n;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (g < len && s[*n] != '\0')
	{
		tab[g] = s[*n];
		g++;
		*n += 1;
	}
	tab[g] = '\0';
	return (tab);
}

char	**split_cub3d(char const *s, char c)
{
	char	**result;
	int		n;
	int		a;

	result = malloc((mk_word(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	n = 0;
	a = 0;
	while (a < mk_word(s, c))
	{
		result[a] = mk_strpush(s, c, &n);
		if (!result[a])
		{
			mk_free(result, a);
			return (NULL);
		}
		a++;
	}
	result[a] = NULL;
	return (result);
}