/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:31:36 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:04 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*izdead(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->p_arg->t2die + 1);
	pthread_mutex_lock(&philo->p_arg->time_eat);
	pthread_mutex_lock(&philo->p_arg->finish);
	if (!check_if_dead(philo, 0) && !philo->finish && ((current_time()
				- philo->ms_last_eat) >= (long long unsigned)
			(philo->p_arg->t2die)))
	{
		pthread_mutex_unlock(&philo->p_arg->time_eat);
		pthread_mutex_unlock(&philo->p_arg->finish);
		pthread_mutex_lock(&philo->p_arg->write_mutex);
		write_status(DIED, philo);
		pthread_mutex_unlock(&philo->p_arg->write_mutex);
		check_if_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->p_arg->time_eat);
	pthread_mutex_unlock(&philo->p_arg->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		ft_usleep(philo->p_arg->t2eat / 10);
	while (!check_if_dead(philo, 0))
	{
		pthread_create(&philo->th_death_id, NULL, izdead, data);
		occupation(philo);
		pthread_detach(philo->th_death_id);
		if ((int)++philo->total_eat == philo->p_arg->nb2eat)
		{
			pthread_mutex_lock(&philo->p_arg->finish);
			philo->finish = 1;
			philo->p_arg->nb_philo_ate++;
			if (philo->p_arg->nb_philo_ate == philo->p_arg->nb_philo)
			{
				pthread_mutex_unlock(&philo->p_arg->finish);
				check_if_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->p_arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	threading(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->arg.nb_philo)
	{
		common->philo[i].p_arg = &common->arg;
		if (pthread_create(&common->philo[i].th_id, NULL, thread,
				&common->philo[i]) != 0)
			return (ft_exit(ERROR_PTHREAD));
		i++;
	}
	return (1);
}
