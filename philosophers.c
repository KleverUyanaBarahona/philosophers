/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarahon <kbarahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:18:59 by klever            #+#    #+#             */
/*   Updated: 2021/10/15 20:25:45 by kbarahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	start_process(t_philosophers *lst_philos)
{
	start_philos(lst_philos, lst_philos->size_lst);
	join_threads(lst_philos, lst_philos->size_lst);
	free_resources(lst_philos, lst_philos->size_lst);
}

static int	create_lst_philos(int argc, char *argv[])
{
	t_philosophers	*lst_philos;
	int				i;
	int				num_philo;

	if ((argc == 5 || argc == 6) && check_arg(argv))
	{
		if (argv[5] && mini_atoi(argv[5]) == 0)
			return (0);
		num_philo = mini_atoi(argv[1]);
		i = 2;
		lst_philos = new_philo(1, new_time(argv), num_philo);
		while (i <= num_philo)
		{
			add_philos(&lst_philos, new_philo(i, new_time(argv), num_philo));
			i++;
		}
		start_process(lst_philos);
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	if (create_lst_philos(argc, argv) == 0)
		printf("philo: Error syntax arguments\n");
	return (0);
}
