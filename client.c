/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperegri <cperegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:05:59 by cperegri          #+#    #+#             */
/*   Updated: 2022/03/26 16:57:40 by cperegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_error(char *str)
{
	while (*str)
		write(1, str++, 1);
	exit(0);
	return (0);
}

static int	ft_send_bit(int pid, int i, char c)
{
	if (c >> i & 1)
	{
		if (kill(pid, SIGUSR1) < 0)
			return (ft_error("WRONG_PID_NUMBA\n"));
	}
	else
	{
		if (kill(pid, SIGUSR2) < 0)
			return (ft_error("WRONG_PID_NUMBA\n"));
	}
	return (1);
}

static void	ft_send_string(int pid, char *str)
{
	int		i;

	while (*str)
	{
		i = 8;
		while (i--)
		{
			if (!ft_send_bit(pid, i, *str))
				return ;
			usleep(400);
		}
		str++;
		usleep(400);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_send_string(pid, argv[2]);
	}
	else
		ft_error("WRONG_ARGUMENT_NUMBA\n");
	return (0);
}
