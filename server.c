/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperegri <cperegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:17:05 by cperegri          #+#    #+#             */
/*   Updated: 2022/03/26 16:55:58 by cperegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sigaction(int sig, siginfo_t *info, void *cont)
{
	static int	bitnum;
	static char	c = 0;

	(void)info;
	(void)cont;
	c = c | (sig == SIGUSR1);
	if (bitnum++ == 7)
	{
		bitnum = 0;
		write(1, &c, 1);
		c = 0;
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
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
	return (0);
}
