/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:28:09 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:02 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

int	izdigits(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	parsing_args(int ac, char **av, t_common *common)
{
	if ((ac == 5 || ac == 6) && izdigits(av, 0, 1))
	{
		common->arg.nb_philo = ft_atoi(av[1]);
		common->arg.t2die = ft_atoi(av[2]) * 1000;
		common->arg.t2eat = ft_atoi(av[3]) * 1000;
		common->arg.t2sleep = ft_atoi(av[4]) * 1000;
		common->arg.nb2eat = -1;
		if (ac == 6)
			common->arg.nb2eat = ft_atoi(av[5]);
		if (common->arg.nb_philo <= 0 || common->arg.t2die <= 0
			|| common->arg.t2eat <= 0 || common->arg.t2sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

void	init_mutex(t_common *common)
{
	pthread_mutex_init(&common->arg.write_mutex, NULL);
	pthread_mutex_init(&common->arg.dead, NULL);
	pthread_mutex_init(&common->arg.time_eat, NULL);
	pthread_mutex_init(&common->arg.finish, NULL);
}

int	initialize(t_common *common)
{
	int	i;

	i = 0;
	common->arg.start_diner = current_time();
	common->arg.stop_diner = 0;
	common->arg.nb_philo_ate = 0;
	init_mutex(common);
	while (i < common->arg.nb_philo)
	{
		common->philo[i].name = i + 1;
		common->philo[i].ms_last_eat = common->arg.start_diner;
		common->philo[i].total_eat = 0;
		common->philo[i].finish = 0;
		common->philo[i].right_fork = NULL;
		pthread_mutex_init(&common->philo[i].left_fork, NULL);
		if (common->arg.nb_philo == 1)
			return (1);
		if (i == common->arg.nb_philo - 1)
			common->philo[i].right_fork = &common->philo[0].left_fork;
		else
			common->philo[i].right_fork = &common->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}
