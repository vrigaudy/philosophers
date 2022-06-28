/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:20:59 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/20 20:50:37 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static void	*ft_routine(void *arg)
{
	int		nbr;
	t_philo	*philo;	

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->table_access);
	nbr = philo->table->philo_nbr;
	pthread_mutex_unlock(&philo->table->table_access);
	if (nbr <= 1)
		ft_routine_1(philo);
	if (philo->id % 2 == 0)
		ft_routine_think(philo);
	while (ft_check_end(philo) == 0)
	{
		ft_routine_eat(philo);
		if (ft_check_end(philo) == 0)
		{
			ft_print(philo, "is sleeping");
			ft_usleep(philo, philo->time_to_sleep);
		}
		ft_routine_think(philo);
	}
	return (NULL);
}

static void	ft_do_thread(t_philo *philo)
{
	int	i;
	int	err;

	i = philo->table->philo_nbr;
	while (i)
	{
		err = pthread_create(&philo->thread, NULL, ft_routine, (void *)philo);
		if (err)
			return ;
		philo = philo->next;
		i--;
	}
	while (i < philo->table->philo_nbr)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

void	ft_free(t_philo *philo)
{
	if (philo->next->id != 1)
		ft_free(philo->next);
	else
	{
		pthread_mutex_destroy(&philo->table->table_access);
		free(philo->table);
	}
	pthread_mutex_destroy(&philo->fork);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_table	*table;

	philo = NULL;
	table = NULL;
	if (ft_parse(ac, av) == 0)
	{
		table = ft_table_init(ac, av);
		philo = ft_data_init(table);
		if (philo)
		{
			ft_do_thread(philo);
			ft_free(philo);
		}
	}
	return (0);
}
