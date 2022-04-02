/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperegri <cperegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:18:22 by cperegri          #+#    #+#             */
/*   Updated: 2022/03/26 15:21:10 by cperegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *s);

#endif
