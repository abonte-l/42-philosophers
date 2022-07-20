/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonte-l <abonte-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:40:34 by abonte-l          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:01 by abonte-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ARG "[ERROR] Invalid Arguments\n"
# define ERROR_MALLOC "[ERROR] Malloc returned NULL\n"
# define ERROR_PTHREAD "[ERROR] Pthread did not return 0\n"
# define ERROR_GTOTD "Gettimeofday returned -1\n"

# define TOOK_A_FORK "has taken a fork\n"
# define THINKING "is thinking\n"
# define SLEEPING "is sleeping\n"
# define EATING "is eating\n"
# define DIED "died\n"

typedef struct s_arg
{
	int											nb_philo;
	int											nb2eat;
	int											nb_philo_ate;
	long long unsigned int						t2die;
	long long unsigned int						t2eat;
	long long unsigned int						t2sleep;
	long long unsigned int						stop_diner;
	long long unsigned int						start_diner;
	pthread_mutex_t								write_mutex;
	pthread_mutex_t								dead;
	pthread_mutex_t								time_eat;
	pthread_mutex_t								finish;
}							t_arg;

typedef struct s_philo
{
	t_arg								*p_arg;
	int									name;
	int									finish;
	unsigned int						total_eat;
	long long unsigned int				ms_last_eat;
	pthread_t							th_id;
	pthread_t							th_death_id;
	pthread_mutex_t						*right_fork;
	pthread_mutex_t						left_fork;
}							t_philo;

typedef struct s_common
{
	t_philo					*philo;
	t_arg					arg;
}							t_common;

int							parsing_args(int ac, char **av, t_common *p);
int							initialize(t_common *p);
int							ft_exit(char *str);
int							threading(t_common *p);
int							check_if_dead(t_philo *philo, int i);
int							ft_strlen(char *str);
long long unsigned int		current_time(void);
void						write_status(char *str, t_philo *philo);
void						ft_putstr_fd(char *s, int fd);
void						ft_usleep(long long unsigned int time_in_ms);
void						occupation(t_philo *philo);

#endif
