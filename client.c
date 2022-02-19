/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:58:43 by alukongo          #+#    #+#             */
/*   Updated: 2022/02/19 15:48:16 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"
#include <sys/types.h> 

/**
 * @brief 
 * i = the index of my binary digits
 * av & (1 << i) = i make a logical operator "AND" in digits binary of charactor av with a digit who gone be = 1 in position i
 * @param pid = the pid of the client
 * @param av = the charactor who i want send
 * if av & (1 << i) = 1 i send SIGUSR1 else i send SIGUSR2
 * i use a sleep because i want give some time to my server to received the signal and to treat it
 */
void	ft_send_signal(int pid, char av)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (i <= 7)
	{
		if (av & (1 << i))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (ret)
		{
			write(1, "Error sending signal to server\n", 32);
			exit(1);
		}
		usleep(100);
		i++;
	}
	usleep(100);
}

void	confirmation(int signal)
{
	static int	nb_char = 0;

	if (signal == SIGUSR1)
		nb_char++;
	else
	{
		write(1, "nb of char = ", 13);
		ft_putnbr(nb_char);
		ft_putchar('\n', 1);
		write(1, "char correctly receved", 23);
		exit(1);
	}
}



void error(int ac, char *av)
{
	int i;

	i = 0;
	if (ac != 3)
	{
		write(1, "Usage : ./client <pid> <message>\n", 33);
		exit(1);
	}
	while(av[i])
	{
		if(!ft_isdigit(av[i]))
		{
			write(1, "PID is not a valid number\n", 26);
			exit(1);
		}
		i++;
	}
	if (!ft_atoi(av))
	{
		write(1, "PID is not a valid number\n", 26);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	error(ac, av[1]);
	while (av[2][i])
	{
		signal(SIGUSR1, confirmation);
		signal(SIGUSR2, confirmation);
		ft_send_signal(ft_atoi(av[1]), av[2][i]);
		i++;
	}
	ft_send_signal(ft_atoi(av[1]), av[2][i]);
	while(1)
		pause();
	return (0);
}
