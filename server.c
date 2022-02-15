/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:58:00 by alukongo          #+#    #+#             */
/*   Updated: 2022/02/15 16:56:59 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void handler_sig(int signal, siginfo_t *info, void *context)
{
	static unsigned char 	c = 0;
	static int				i = 0;
	
	(void)info;
	(void)context;
	if (i < 8)
	{
		if(signal == SIGUSR1)
			c = c | (1 << i);
		i++;
	}
	if (i == 8)
	{
		if(!c)
		{
			kill(info->si_pid, SIGUSR2);
			return ;

		}
		ft_putchar(c, 1);
		i = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}


int main()
{
	struct sigaction t1;
	t1.sa_sigaction = handler_sig;
	t1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &t1, NULL);
	sigaction(SIGUSR2, &t1, NULL);
	
	printf("%d\n", getpid());
	while(1)
		pause();
	ft_putchar('\n', 1);
}