/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:23:02 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/21 20:07:21 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int	ft_atoi(const char *str)
{
	int	neg;
	int	total;

	neg = 1;
	total = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -neg;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - 48);
		str++;
	}
	return (total * neg);
}

int	ft_gettime(struct timeval start)
{
	int				time;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_philo *philo, int time)
{
	gettimeofday(&philo->action_start, NULL);
	while (ft_check_end(philo) == 0
		&& ft_check_end(philo->next) == 0
		&& ft_gettime(philo->action_start) < time)
		usleep(100);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->table_access);
	if (philo->table->dead == 0 && philo->table->max_eat_count != 0)
		printf("%d %d %s\n", ft_gettime(philo->start), philo->id, str);
	pthread_mutex_unlock(&philo->table->table_access);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
