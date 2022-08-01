/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalayir <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:30:45 by acalayir          #+#    #+#             */
/*   Updated: 2022/07/05 11:31:01 by acalayir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
		ret = ret * 10 + (*str++ - '0');
	return (ret);
}

int	ft_strlen(char *s)
{
	int	ret;

	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}

int	ft_strncmp(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (*str_1 && *str_2 && i < n)
	{
		if (*str_1 != *str_2)
			return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
		++str_1;
		++str_2;
		++i;
	}
	if (i == n)
	{
		--str_1;
		--str_2;
	}
	return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
}

long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}

void	ft_usleep(unsigned int n)
{
	long	start_ts;
	long	step_ts;

	start_ts = get_ts();
	while (1)
	{
		step_ts = get_ts();
		if ((step_ts - start_ts) * 1000 >= n)
			break ;
		usleep(500);
	}
}
