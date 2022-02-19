/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:58:00 by alukongo          #+#    #+#             */
/*   Updated: 2022/02/19 19:09:29 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include "minitalk.h"

/**
 * @brief 
 * i = the index of binary value of my variable c, i limite it at 8 because char = 1 byte so 8 digit
 * line 33 to 38: if i received SIGUSR1 i put a 1 in the binary value of the position i
 * line 39 to 49: if i = 8, i check the value of c, if c = 0 i send SIGUSR2 else i print c send SIGUSR1
 * @param signal it the value of the signal receveid
 * @param info it containe the information of the programme where the signal it come from
 */
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
	ft_putnbr(getpid()); //i print the pid
	ft_putchar('\n', 1);
	while(1)
		pause();
}