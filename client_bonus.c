/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperegri <cperegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:17:33 by cperegri          #+#    #+#             */
/*   Updated: 2022/03/26 17:41:34 by cperegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_error(char *str)
{
	while (*str)
		write(1, str++, 1);
	exit(0);
	return (1);
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
	return (0);
}

static void	ft_send_string(int pid, char *str)
{
	int		i;

	while (*str)
	{
		i = 8;
		while (i--)
		{
			if (ft_send_bit(pid, i, *str))
				exit (0);
			usleep(350);
		}
		str++;
		usleep(350);
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		usleep(300);
	}
}

static void	ft_recieve(int sig, siginfo_t *info, void *cont)
{
	(void)info;
	(void)cont;
	if (sig == SIGUSR2)
	{
		write (1, "I_KNOW_YOU_SAW_MY_SMS\n", 22);
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sig;
	int					pid;

	s_sig.sa_sigaction = ft_recieve;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_send_string(pid, argv[2]);
	}
	else
		ft_error("WRONG_ARGUMENT_NUMBA\n");
	while (1)
		pause();
	return (0);
}
