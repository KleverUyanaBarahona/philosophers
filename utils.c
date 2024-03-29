/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 03:09:01 by klever            #+#    #+#             */
/*   Updated: 2021/10/13 19:22:47 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	print_status(t_philosophers *philo, char *message)
{
	uint64_t	diff;

	diff = get_time() - philo->start;
	pthread_mutex_lock(philo->print);
	if (philo->time_to->tic_toc > 0 && *philo->die == 0)
		printf(GRAY"%llu\033[1;36m %d %s\n\033[1;37m", diff,
			  philo->num, message);
	pthread_mutex_unlock(philo->print);
}

uint64_t	get_time(void)
{
	static struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000));
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_arg(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	mini_atoi(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (!*str)
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += str[i] - '0';
		if (str[i + 1] != '\0')
			nb *= 10;
		else
			return (nb);
		i++;
	}
	return (-1);
}
