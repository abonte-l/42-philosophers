/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_occup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:33:09 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:03 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(char *str, t_philo *philo)
{
	long long unsigned int		time;

	time = -1;
	time = current_time() - philo->p_arg->start_diner;
	if (time >= 0 && time <= 4294967295 && !check_if_dead(philo, 0))
	{
		printf("%llu ", time / 1000);
		printf("Philo %d %s", philo->name, str);
	}
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_arg->write_mutex);
	write_status(SLEEPING, philo);
	pthread_mutex_unlock(&philo->p_arg->write_mutex);
	ft_usleep(philo->p_arg->t2sleep);
	pthread_mutex_lock(&philo->p_arg->write_mutex);
	write_status(THINKING, philo);
	pthread_mutex_unlock(&philo->p_arg->write_mutex);
}

void	occupation(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->p_arg->write_mutex);
	write_status(TOOK_A_FORK, philo);
	pthread_mutex_unlock(&philo->p_arg->write_mutex);
	if (!philo->right_fork)
	{
		ft_usleep(philo->p_arg->t2die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->p_arg->write_mutex);
	write_status(TOOK_A_FORK, philo);
	pthread_mutex_unlock(&philo->p_arg->write_mutex);
	pthread_mutex_lock(&philo->p_arg->write_mutex);
	write_status(EATING, philo);
	pthread_mutex_lock(&philo->p_arg->time_eat);
	philo->ms_last_eat = current_time();
	pthread_mutex_unlock(&philo->p_arg->time_eat);
	pthread_mutex_unlock(&philo->p_arg->write_mutex);
	ft_usleep(philo->p_arg->t2eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	sleep_think(philo);
}
