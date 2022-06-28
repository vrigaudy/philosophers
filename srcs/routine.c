/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:54:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/21 20:34:48 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	ft_routine_think(t_philo *philo)
{
	if (ft_check_end(philo) == 0)
	{
		ft_print(philo, "is thinking");
		usleep(300);
	}
}

void	ft_routine_1(t_philo *philo)
{
	ft_print(philo, "has taken a fork");
	while (ft_check_end(philo) == 0)
		usleep(100);
}

void	ft_eat_count(t_philo *philo)
{
	philo->meal_nbr++;
	if (philo->meal_nbr == philo->max_eat)
	{
		pthread_mutex_lock(&philo->table->table_access);
		philo->table->max_eat_count--;
		if (philo->table->max_eat_count == 0)
			printf("%d All philosophers have eaten\n", ft_gettime(philo->start));
		pthread_mutex_unlock(&philo->table->table_access);
	}
}

int	ft_check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_access);
	if (ft_gettime(philo->last_meal) > philo->time_to_die
		&& philo->table-> dead == 0)
	{
		printf("%d %d died\n", ft_gettime(philo->start), philo->id);
		philo->table->dead++;
	}
	if (philo->table->dead == 0 && philo->table->max_eat_count > 0)
	{
		pthread_mutex_unlock(&philo->table->table_access);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->table_access);
		return (1);
	}
}

void	ft_routine_eat(t_philo *philo)
{
	if (ft_check_end(philo) == 0)
	{
		if (philo->id % 2 == 1)
			pthread_mutex_lock(&philo->fork);
		else
			pthread_mutex_lock(&philo->next->fork);
		ft_print(philo, "has taken a fork");
		if (philo->id % 2 == 1)
			pthread_mutex_lock(&philo->next->fork);
		else
			pthread_mutex_lock(&philo->fork);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		pthread_mutex_lock(&philo->table->table_access);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&philo->table->table_access);
		ft_usleep(philo, philo->time_to_eat);
		if (ft_check_end(philo) == 0)
			ft_eat_count(philo);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}
