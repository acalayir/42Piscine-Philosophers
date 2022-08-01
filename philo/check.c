/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalayir <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:31:33 by acalayir          #+#    #+#             */
/*   Updated: 2022/07/05 11:31:35 by acalayir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	else if (ft_atoi(str) == 2147483647)
		return (0);
	return (1);
}

int	invalid_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!is_valid(argv[i]))
			return (1);
	return (0);
}

void	s_sleep(t_philo *p, long long ms)
{
	long long	begin;

	begin = gettime(&p->start);
	while (gettime(&p->start) - begin < ms)
		usleep(100);
}

long long	gettime(struct timeval *s)
{
	struct timeval	e;
	long long		s_ms;
	long long		e_ms;

	gettimeofday(&e, NULL);
	s_ms = s->tv_sec * 1000LL + s->tv_usec / 1000;
	e_ms = e.tv_sec * 1000LL + e.tv_usec / 1000;
	return (e_ms - s_ms);
}
