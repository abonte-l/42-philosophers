/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:37:16 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/19 19:47:38 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_if_dead2(t_common *common)
{
	pthread_mutex_lock(&common->arg.dead);
	if (common->arg.stop_diner)
	{
		pthread_mutex_unlock(&common->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&common->arg.dead);
	return (0);
}

void	stop(t_common *common)
{
	int	i;

	i = -1;
	while (!check_if_dead2(common))
		ft_usleep(1);
	while (++i < common->arg.nb_philo)
		pthread_join(common->philo[i].th_id, NULL);
	pthread_mutex_destroy(&common->arg.write_mutex);
	i = -1;
	while (++i < common->arg.nb_philo)
		pthread_mutex_destroy(&common->philo[i].left_fork);
	if (common->arg.stop_diner == 2)
		printf("Each philosopher ate %d time(s)\n", common->arg.nb2eat);
	free(common->philo);
}

int	main(int ac, char **av)
{
	t_common		common;

	if (!(parsing_args(ac, av, &common)))
		return (ft_exit(ERROR_ARG));
	common.philo = malloc(sizeof(t_philo) * common.arg.nb_philo);
	if (!common.philo)
		return (ft_exit(ERROR_MALLOC));
	if (!initialize(&common) || !threading(&common))
	{
		free(common.philo);
		return (0);
	}
	stop(&common);
}
