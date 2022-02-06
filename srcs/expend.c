/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:13:38 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 07:06:15 by anclarma         ###   ########.fr       */
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

typedef struct s_expend_stuff	t_expend_stuff;
struct	s_expend_stuff
{
	t_cmd	**cmd;
	t_stuff	*stuff;
	char	**envp;
};

// void	expend_step1(t_cmd *tmp, t_cmd *tmp_del)
// {
// 	tmp = tmp_del->next;
// 	if (tmp_del->next != NULL)
// 		tmp_del->next = tmp_del->next->next;
// 	if (tmp != NULL)
// 		free(tmp->word);
// 	free(tmp);
// }

// void	expend_step2(t_cmd **cmd, t_cmd *tmp)
// {
// 	*cmd = (*cmd)->next;
// 	if (tmp != NULL)
// 		free(tmp->word);
// 	free(tmp);
// }

// void	expend_step3(char *word, int i, int j, t_expend_stuff *st)
// {
// 	char	*first;
// 	t_cmd	*new;

// 	first = ft_strndup(word + j, i - j);
// 	new = lzac_ft_lstnew(first, ARGUMENT, st->stuff->space);
// 	lzac_ft_lstadd_back(st->cmd, new);
// }

// void	sub_expend_step4(char *word, t_stuff *stuff, t_cmd **cmd)
// {
// 	t_cmd	*new;

// 	new = lzac_ft_lstnew(word, ARGUMENT, stuff->space);
// 	lzac_ft_lstadd_back(cmd, new);
// 	stuff->space = 0;
// }

// void	expend_step4(char *word, int *i, int *j, t_expend_stuff *st)
// {
// 	char	*first;
// 	char	*sec;

// 	while (word[*i])
// 	{
// 		if (word[*i] == '$' && (word[*i + 1] != ' ' || word[*i + 1] != '|'))
// 		{
// 			first = ft_strndup(word + *j, *i - *j);
// 			if (first[0] != 0)
// 				sub_expend_step4(first, st->stuff, st->cmd);
// 			else
// 				free(first);
// 			sec = ft_expend_quote(word, i, st->envp);
// 			if (sec != NULL)
// 				sub_expend_step4(sec, st->stuff, st->cmd);
// 			*j = *i;
// 		}
// 		else
// 			*i = *i + 1;
// 	}
// }

void	expend_in_quote(char **envp, t_cmd **cmd, t_stuff *stuff)
{
	t_cmd			*tmp;
	t_cmd			*tmp_del;
	int				ij[2];
	t_expend_stuff	st;

	st = (t_expend_stuff){.cmd = cmd, .stuff = stuff, .envp = envp};
	ij[0] = 0;
	ij[1] = 0;
	tmp = ft_cmdlast(*cmd);
	tmp_del = *cmd;
	while (tmp_del && tmp_del->next && tmp_del->next->next)
		tmp_del = tmp_del->next;
	while (tmp && tmp->word && tmp->word[ij[0]] && !(tmp->word[ij[0]] == '$'
			&& (tmp->word[ij[0] + 1] != ' ' || tmp->word[ij[0] + 1] != '|')))
		ij[0]++;
	if (tmp && ij[0] == (int)ft_strlen(tmp->word))
		return ;
	expend_step4(tmp->word, ij + 0, ij + 1, &st);
	if (ij[1] < ij[0])
		expend_step3(tmp->word, ij[0], ij[1], &st);
	if (ft_cmdsize(*cmd) - 1 == 0)
		expend_step2(cmd, tmp);
	else
		expend_step1(tmp, tmp_del);
	return ;
}
