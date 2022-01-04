/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/04 11:50:24 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

/*
** ft_cd
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/
int	ft_cd(int ac, char **av, t_list **env)
{
	int			step;
	t_cd		cd_var;
	static int	(*fonc_step[10])(t_cd *) = {step0, step1, step2, step3, step4,
		step5, step6, step7, step8, step9};

	cd_var = (t_cd){.env = env};
	if (ac >= 2)
		cd_var.operand = ft_strdup(av[1]);
	step = 0;
	while (step < 10)
		step = (fonc_step[step])(&cd_var);
	//Si, pendant l'exécution des étapes ci-dessus,
	//la variable d'environnement PWD est définie,
	//la variable d'environnement OLDPWD doit également
	//être définie sur la valeur de l'ancien répertoire de travail
	//(c'est-à-dire le répertoire de travail actuel
	//immédiatement avant l'appel à cd ).
	free(cd_var.curpath);
	free(cd_var.operand);
	free(cd_var.new_pwd);
	return (cd_var.ret);
}
