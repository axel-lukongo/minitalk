/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:58:43 by alukongo          #+#    #+#             */
/*   Updated: 2022/02/21 16:27:28 by alukongo         ###   ########.fr       */
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
 * av & (1 << i) = i make a logical operator "AND" in digits binary
  of charactor av with a digit who gone be = 1 in position i
 
 * @param pid = the pid of the server
 * @param av = the charactor who i want send
 * if av & (1 << i) = 1 i send SIGUSR1 else i send SIGUSR2
 
 * i use a usleep because i want give some time to my server
   to received the signal and to treat it
 */
static void	ft_send_signal(int pid, char *av)
{
	int		i;

	while (*av)
	{
		i = 8;
		while (i--)
		{
			if (*av >> i & 1 >> 0)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
		av++;
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

/**
 * comfirmation
 
 * line 74 if i receveid SIGUSR1 it mean i do not have yet 
  send all char of av[1] so i increment nb_char
 
 * line 76 if i send all the char and i received SIGUSR2,
  it mean i send a '\0', so i print the number of char.
 
 * @param signal is the value of the signal who i received
 */
void	confirmation(int signal)
{
	static int	nb_char = 0;

	if (signal == SIGUSR1)
		nb_char++;
	else
	{
		write(1, "nb of char = ", 13);
		ft_putnbr(nb_char);
		ft_putchar_fd('\n', 1);
		write(1, "char correctly receved", 23);
		exit(0);
	}
}

/**

 * error 
 * line 100 i verify if i have 3 argument, !not more and not less!
 * line 107 i verify if i only have a digit in my pid
 * line 114 i check if my pid is bigger than 0 
 * @param ac is the number of argument
 * @param av my string
 */
void	error(int ac, char *av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		write(1, "Usage : ./client <pid> <message>\n", 33);
		exit(1);
	}
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
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
	error(ac, av[1]);
	signal(SIGUSR1, confirmation);
	signal(SIGUSR2, confirmation);
	ft_send_signal(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}
