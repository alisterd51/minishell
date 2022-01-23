/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:45:24 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/23 05:30:33 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	clean_tab(char ***tab)
{
	int	i;

	i = 0;
	if (*tab == NULL)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static size_t	linesize(char *line)
{
	size_t	count;

	count = 0;
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			count++;
			while (*line && !ft_isspace(*line))
				line++;
		}
		else
			line++;
	}
	return (count);
}

static size_t	strsize(char *line)
{
	size_t	size;

	size = 0;
	while (line[size] && !ft_isspace(line[size]))
		size++;
	return (size);
}

static char	*parse_line_to_str(char **line)
{
	char	*ret;
	size_t	size;

	ret = NULL;
	while (ft_isspace(**line))
		(*line)++;
	size = strsize(*line);
	if (**line)
		ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, *line, size + 1);
	while (**line && !ft_isspace(**line))
		(*line)++;
	return (ret);
}

char	**line_to_tab(char *line)
{
	size_t	size;
	size_t	i;
	char	**ret;

	size = linesize(line);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, sizeof(char *) * (size + 1));
	while (i < size)
	{
		ret[i] = parse_line_to_str(&line);
		if (ret[i] == NULL)
		{
			clean_tab(&ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
/*
char	**parse_quotes(char *line)
{
	size_t	single_quotes;
	size_t	double_quotes;
	size_t	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ''')
			single_quotes++;
		else if (line[i] == '"')
			double_quotes++;
		write(1, line + i, 1);
		if ((single_quotes > 0 || double_quotes > 0)
				&& (single_quotes % 2 == 0 && double_quotes % 2 == 0))
			write(1, "\n", 1);
		i++;
	}
}
*/
