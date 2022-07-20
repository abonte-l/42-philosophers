/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:32:07 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:06 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_if_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->p_arg->dead);
	if (i)
		philo->p_arg->stop_diner = i;
	if (philo->p_arg->stop_diner)
	{
		pthread_mutex_unlock(&philo->p_arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_arg->dead);
	return (0);
}

long long unsigned int	current_time(void)
{
	long long unsigned int			time;
	struct timeval					current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit(ERROR_GTOTD);
	time = (current_time.tv_sec * 1000000) + (current_time.tv_usec);
	return (time);
}

void	ft_usleep(long long unsigned int time_in_us)
{
	long long unsigned int	start_time;

	start_time = 0;
	start_time = current_time();
	while ((current_time() - start_time) < time_in_us)
		usleep(time_in_us);
}
