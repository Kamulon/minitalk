/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperegri <cperegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:17:56 by cperegri          #+#    #+#             */
/*   Updated: 2022/03/26 17:36:50 by cperegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_clean(int *bitnum, char *c, int *zeronum)
{
	*bitnum = 0;
	*c = 0;
	*zeronum = 0;
}

static void	ft_end_char(int *bitnum, char *c, int *zeronum)
{
	ft_putchar_fd(*c, 1);
	ft_clean(bitnum, c, zeronum);
}

static void	ft_sigaction(int sig, siginfo_t *info, void *cont)
{
	static int	bitnum = 0;
	static char	c = 0;
	static int	pid = 0;
	static int	zeronum = 0;

	(void)cont;
	if (!pid || pid != info->si_pid)
	{
		ft_clean(&bitnum, &c, &zeronum);
		pid = info->si_pid;
	}
	c = c | (sig == SIGUSR1);
	zeronum += (sig == SIGUSR2);
	if (bitnum++ == 7)
	{
		if (zeronum == 8)
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		ft_end_char(&bitnum, &c, &zeronum);
		kill(info->si_pid, SIGUSR1);
	}
	else
		c = c << 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sig;

	(void)argc;
	(void)argv;
	write (1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sig.sa_sigaction = ft_sigaction;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
	return (0);
}
