/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:50:05 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/06/20 21:03:57 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define PHILO_H

# define SUCCESS 0
# define INPUT_ERROR 1
# define MALLOC_ERROR 2

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	struct timeval	start;
	pthread_mutex_t	table_access;
	int				dead;
	int				max_eat_count;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				meal_nbr;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_table	*table;
	struct s_philo	*next;
	struct timeval	start;
	struct timeval	last_meal;
	struct timeval	action_start;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		ft_parse(int ac, char **av);
int		ft_check_end(t_philo *philo);
int		ft_gettime(struct timeval start);

void	ft_routine_1(t_philo *philo);
void	ft_routine_eat(t_philo *philo);
void	ft_routine_think(t_philo *philo);
void	ft_usleep(t_philo *philo, int time);
void	ft_print(t_philo *philo, char *str);
void	ft_lst_init(t_philo *philo, t_table *table);

t_philo	*ft_data_init(t_table *table);

t_table	*ft_table_init(int ac, char **av);

#endif
