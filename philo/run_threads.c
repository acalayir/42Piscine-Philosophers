/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalayir <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:31:49 by acalayir          #+#    #+#             */
/*   Updated: 2022/07/30 17:00:59 by acalayir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *ph, int rank)
{
	long long	s;

	s = gettime(&ph->start);
	pthread_mutex_lock(&ph->rook);
	ph->last_eat[rank] = s;
	print(ph, "is eating\n", s, rank + 1);
	if (++ph->eaten[rank] == ph->serving_count)
		ph->eaten_count--;
	pthread_mutex_unlock(&ph->rook);
	s_sleep(ph, ph->eat_time);
}

void	*live(void *arg)
{
	t_philo	*ph;
	int		rank;

	rank = ((t_arg *)arg)->rank;
	ph = ((t_arg *)arg)->philos;
	if (rank % 2)
		usleep(15000);
	while (!ph->is_dead)
	{
		pthread_mutex_lock(&ph->forks[rank]);
		print(ph, "has taken a fork\n", gettime(&ph->start), rank + 1);
		pthread_mutex_lock(&ph->forks[(rank + 1) % ph->count]);
		print(ph, "has taken a fork\n", gettime(&ph->start), rank + 1);
		philo_eat(ph, rank);
		pthread_mutex_unlock(&ph->forks[(rank + 1) % ph->count]);
		pthread_mutex_unlock(&ph->forks[rank]);
		if (!ph->eaten_count)
			return (0);
		print(ph, "is sleeping\n", gettime(&ph->start), rank + 1);
		s_sleep(ph, ph->sleep_time);
		usleep(1000);
	}
	return (0);
}

void	*eat_ctrl(void	*ph_arg)
{
	t_philo	*ph;

	ph = (t_philo *)ph_arg;
	while (1)
	{
		pthread_mutex_lock(&ph->rook);
		if (ph->eaten_count == 0)
			break ;
		pthread_mutex_unlock(&ph->rook);
	}
	pthread_mutex_unlock(&ph->rook);
	return (0);
}

void	run_threads(t_philo *ph)
{
	t_arg	*philo_args;
	int		i;

	philo_args = (t_arg *)malloc(ph->count * sizeof(t_arg));
	i = -1;
	while (++i < ph->count)
	{
		philo_args[i].rank = i;
		philo_args[i].philos = ph;
	}
	gettimeofday(&ph->start, NULL);
	i = -1;
	while (++i < ph->count)
	{
		pthread_create(&ph->thread_id[i], NULL, live, &philo_args[i]);
		pthread_detach(ph->thread_id[i]);
	}
}
