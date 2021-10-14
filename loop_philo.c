/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:54:09 by klever            #+#    #+#             */
/*   Updated: 2021/10/14 17:59:19 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	loop_must_eat(t_philosophers *philo)
{
	while (*philo->time_to->tmp_must_eat < philo->size_lst)
	{
		eat_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
		sleep_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
		think_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
		if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		{
			free_fork(philo);
			break ;
		}
	}
}

void	loop_without_must_eat(t_philosophers *philo)
{
	while (1)
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
		if (philo->time_to->tic_toc <= 0 || *philo->die == 1)
		{
			free_fork(philo);
			break ;
		}
	}
}