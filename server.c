/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:58:00 by alukongo          #+#    #+#             */
/*   Updated: 2022/02/21 17:05:45 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include "minitalk.h"

void	handler_sig(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c |= (signal == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	t1;

	t1.sa_sigaction = handler_sig;
	t1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &t1, NULL);
	sigaction(SIGUSR2, &t1, NULL);
	ft_putnbr(getpid());
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
