/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:51:30 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 10:22:42 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

char	*search_env(char **envp, char *word)
{
	int		i;
	char	*str;
	char	*key;

	i = 0;
	str = NULL;
	if (!envp)
		return (NULL);
	key = ft_strjoin(word, "=");
	free(word);
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)) != 0)
		i++;
	if (envp[i] && (ft_strncmp(envp[i], key, ft_strlen(key)) == 0))
	{
		str = envp[i];
		str = str + ft_strlen(key);
		free(key);
		return (ft_strdup(str));
	}
	free(key);
	return (NULL);
}

void	ft_expend(t_stuff *stuff, char **envp, t_cmd **cmd)
{
	t_cmd	*new;
	char	*word;
	int		j;

	j = 0;
	stuff->i = stuff->i + 1;
	stuff->type = ARGUMENT;
	j = ft_expstrclen(stuff->str + stuff->i, ' ');
	if (j == 0)
	{
		word = "$";
		stuff->type = DOLLAR;
	}
	else
	{
		word = ft_strndup(stuff->str + stuff->i, j);
		if (word && word[0] == '?')
			word = ft_itoa(ft_get_status());
		else
			word = search_env(envp, word);
		if (word == NULL)
		{
			stuff->i = stuff->i + 1;
			free(word);
			stuff->i = stuff->i + j - 1;
			return ;
		}
	}
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i = stuff->i + j;
}

char	*ft_expend_quote(char *word, int *i, char **envp)
{
	int		j;

	j = 0;
	*i = *i + 1;
	j = ft_expstrclen(word + *i, ' ');
	word = ft_strndup(word + *i, j);
	if (word && word[0] == '?')
		word = ft_itoa(ft_get_status());
	else
		word = search_env(envp, word);
	if (word == NULL)
	{
		*i = *i + 1;
		free(word);
		*i = *i + j - 1;
		return (NULL);
	}
	(*i) += j;
	return (word);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
