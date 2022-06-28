/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:50:49 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/20 22:34:34 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	ft_count_arg(int ac)
{
	if (ac <= 6 && ac >= 5)
		return (SUCCESS);
	else
	{
		printf("ERROR : Incorrect number of arguments\n");
		return (INPUT_ERROR);
	}
}

static int	ft_is_int(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("ERROR : Non numerical values detected\n");
				return (INPUT_ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_check_val(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) < 1 || ft_strlen(av[i]) > 10)
		{
			printf("ERROR : Values given exceed processing capabilities\n");
			return (INPUT_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_parse(int ac, char **av)
{
	int	ret;

	ret = 0;
	ret += ft_count_arg(ac);
	ret += ft_is_int(av);
	ret += ft_check_val(av);
	if (!ret)
		return (SUCCESS);
	else
		return (INPUT_ERROR);
}
