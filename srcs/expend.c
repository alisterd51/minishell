/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:13:38 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/05 23:18:29 by lzaccome         ###   ########.fr       */
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
	stuff->i++;
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
			stuff->i++;
			free(word);
			stuff->i += j - 1;
			return ;
		}
	}
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i += j;
}

char	*ft_expend_quote(char *word, int *i, char **envp)
{
	int		j;

	j = 0;
	(*i)++;
	j = ft_expstrclen(word + *i, ' ');
	word = ft_strndup(word + *i, j);
	if (word && word[0] == '?')
		word = ft_itoa(ft_get_status());
	else
		word = search_env(envp, word);
	if (word == NULL)
	{
		(*i)++;
		free(word);
		(*i) += j - 1;
		return (NULL);
	}
	(*i) += j;
	return (word);
}

void	expend_in_quote(char **envp, t_cmd **cmd, t_stuff *stuff)
{
	t_cmd	*tmp;
	t_cmd	*tmp_del;
	t_cmd	*new;
	char	*first;
	char	*sec;
	int		i;
	int		j;
	int		k;
	char	*word;

	i = 0;
	j = 0;
	k = 0;
	tmp = *cmd;
	tmp_del = *cmd;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		k++;
	}
	if (tmp_del && tmp_del->next)
	{
		while (tmp_del->next->next)
			tmp_del = tmp_del->next;
	}
	while (tmp && tmp->word && tmp->word[i])
	{
		if (tmp->word[i] == '$' && (tmp->word[i + 1] != ' '
				|| tmp->word[i + 1] != '|'))
			break ;
		i++;
	}
	if (tmp && i == (int)ft_strlen(tmp->word))
		return ;
	word = tmp->word;
	while (tmp->word[i])
	{
		if (word[i] == '$' && (word[i + 1] != ' ' || word[i + 1] != '|'))
		{
			first = ft_strndup(word + j, i - j);
			if (first[0] != 0)
			{
				new = lzac_ft_lstnew(first, ARGUMENT, stuff->space);
				lzac_ft_lstadd_back(cmd, new);
				stuff->space = 0;
			}
			else
				free(first);
			sec = ft_expend_quote(word, &i, envp);
			if (sec != NULL)
			{
				new = lzac_ft_lstnew(sec, ARGUMENT, stuff->space);
				lzac_ft_lstadd_back(cmd, new);
				stuff->space = 0;
			}
			j = i;
		}
		else
			i++;
	}
	if (j < i)
	{
		first = ft_strndup(word + j, i - j);
		new = lzac_ft_lstnew(first, ARGUMENT, stuff->space);
		lzac_ft_lstadd_back(cmd, new);
	}
	if (k == 0)
	{
		(*cmd) = (*cmd)->next;
		if (tmp != NULL)
			free(tmp->word);
		free(tmp);
	}
	else
	{
		tmp = tmp_del->next;
		if (tmp_del->next != NULL)
			tmp_del->next = tmp_del->next->next;
		if (tmp != NULL)
			free(tmp->word);
		free(tmp);
	}
	return ;
}
