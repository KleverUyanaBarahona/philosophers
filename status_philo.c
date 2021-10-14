/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:37:32 by klever            #+#    #+#             */
/*   Updated: 2021/10/13 21:12:43 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	eat_philo(t_philosophers *philo)
{
	take_fork(philo);
	if (philo->time_to->must_eat)
		philo->time_to->count_eat++;
	print_status(philo, YELLOW"is eating");
	if (philo->time_to->count_eat == philo->time_to->must_eat)
		(*philo->time_to->tmp_must_eat)++;
	philo->time_to->tic_toc = (philo->time_to->die / 1000);
	if (philo->time_to->eat > philo->time_to->die)
		philo->time_to->tic_toc -= morfeo(philo, philo->time_to->die);
	else
		philo->time_to->tic_toc -= morfeo(philo, philo->time_to->eat);
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
	{
		die_philo(philo);
		return ;
	}
	free_fork(philo);
}

void	sleep_philo(t_philosophers *philo)
{
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		return ;
	print_status(philo, BLUE"is sleeping");
	if (philo->time_to->die < (philo->time_to->sleep + philo->time_to->eat))
		philo->time_to->tic_toc
			-= morfeo(philo, philo->time_to->die - philo->time_to->eat);
	else
		philo->time_to->tic_toc -= morfeo(philo, philo->time_to->sleep);
	if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
	{
		die_philo(philo);
		return ;
	}
}

void	think_philo(t_philosophers *philo)
{
	int			status;

	status = 0;
	if (*philo->die == 1)
		return ;
	if (philo->size_lst > 1)
		print_status(philo, PINK"is thinking");
	while (status == 0)
	{
		if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		{
			die_philo(philo);
			return ;
		}
		if (*philo->num_fork >= 2)
			status = 1;
		philo->start_think = (get_time() - philo->start);
		usleep(1000);
		philo->time_to->tic_toc
			-= ((get_time() - philo->start) - philo->start_think);
	}
}

void	die_philo(t_philosophers *philo)
{
	pthread_mutex_lock(philo->print_die);
	if (*philo->die == 0)
	{
		*philo->die = 1;
		free_fork(philo);
		printf(GRAY"%llu %s\033[1;36m%d %s\033[1;37m",
			get_time() - philo->start, "", philo->num, RED"die");
	}
	pthread_mutex_unlock(philo->print_die);
}

uint64_t	morfeo(t_philosophers *philo, uint64_t time_to)
{
	uint64_t	morfeo;
	uint64_t	time;

	morfeo = 0;
	time = 0;
	while (morfeo < (time_to / 1000))
	{
		time = (get_time() - philo->start);
		usleep(100);
		morfeo += ((get_time() - philo->start) - time);
	}
	return (morfeo);
}