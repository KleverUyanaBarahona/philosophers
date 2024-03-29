/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 22:12:59 by klever            #+#    #+#             */
/*   Updated: 2021/10/14 18:01:07 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	start_philos(t_philosophers *lst_philos, int nun_philo)
{
	t_bool			die;
	int				i;

	die = 0;
	i = 0;
	while (i < nun_philo)
	{
		lst_philos->hilo = (pthread_t *)malloc(sizeof(pthread_t));
		lst_philos->size_lst = nun_philo;
		lst_philos->die = &die;
		pthread_mutex_init(&lst_philos->fork, NULL);
		pthread_create(lst_philos->hilo, NULL,
			table_philos, (void *)lst_philos);
		lst_philos = lst_philos->right;
		i++;
	}
}

void	join_threads(t_philosophers *lst_philos, int n_philos)
{
	t_philosophers	*tmp_ph;
	int				j;

	j = n_philos - 1;
	tmp_ph = lst_philos;
	while (j >= 0)
	{
		pthread_join(*tmp_ph->hilo, NULL);
		tmp_ph = tmp_ph->right;
		j--;
	}	
}

void	free_resources(t_philosophers *lst_philos, int n_philo)
{
	t_philosophers	*tmp_philo;

	pthread_mutex_destroy(lst_philos->print);
	pthread_mutex_destroy(lst_philos->print_die);
	while (n_philo--)
	{
		pthread_mutex_destroy(&lst_philos->fork);
		if (lst_philos->right)
		{
			pthread_detach(*lst_philos->hilo);
			free(lst_philos->hilo);
			free(lst_philos->time_to);
			tmp_philo = lst_philos->right;
			free(lst_philos);
			lst_philos = tmp_philo;
		}
	}
}

void	*table_philos(void *arg)
{
	t_philosophers	*philo;
	static int		num_fork;

	philo = (t_philosophers *)arg;
	num_fork = philo->size_lst;
	philo->num_fork = &num_fork;
	philo->time_to->tic_toc = (long long)(philo->time_to->die / 1000);
	philo->start_think = 0;
	if (philo->size_lst > 1 && (philo->num % 2 == 0
			|| philo->size_lst == philo->num))
		usleep(philo->time_to->eat);
	if (philo->time_to->must_eat >= 1)
		loop_must_eat(philo);
	else
	{
		loop_without_must_eat(philo);
		die_philo(philo);
	}
	return ((void *)0);
}