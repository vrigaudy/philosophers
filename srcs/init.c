/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:59:31 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/20 20:44:13 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

t_table	*ft_table_init(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->dead = 0;
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->max_eat = ft_atoi(av[5]);
	else
		table->max_eat = -1;
	table->max_eat_count = table->philo_nbr;
	pthread_mutex_init(&(table->table_access), NULL);
	gettimeofday(&table->start, NULL);
	return (table);
}

static t_philo	*ft_philo_list_make(int depth, t_table *table)
{
	t_philo	*new;

	if (depth <= 0)
		return (NULL);
	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->table = table;
	new->dead = 0;
	new->id = table->philo_nbr - depth + 1;
	new->time_to_die = new->table->time_to_die;
	new->time_to_eat = new->table->time_to_eat;
	new->time_to_sleep = new->table->time_to_sleep;
	new->max_eat = new->table->max_eat;
	new->meal_nbr = 0;
	pthread_mutex_init(&(new->fork), NULL);
	new->last_meal = new->table->start;
	new->start = new->table->start;
	new->next = ft_philo_list_make(depth - 1, table);
	if (!new->next && depth > 1)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static t_philo	*ft_philo_list_init(t_table *table)
{
	t_philo	*temp;
	t_philo	*philo;

	philo = ft_philo_list_make(table->philo_nbr, table);
	temp = philo;
	while (temp->next)
		temp = temp->next;
	temp->next = philo;
	return (philo);
}

t_philo	*ft_data_init(t_table *table)
{
	t_philo	*philo;

	philo = ft_philo_list_init(table);
	if (!philo)
	{
		free(table);
		return (NULL);
	}
	return (philo);
}
