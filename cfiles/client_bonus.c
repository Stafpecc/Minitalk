/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:58:39 by tarini            #+#    #+#             */
/*   Updated: 2025/02/01 23:21:12 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
		ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", pid);
	ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
	i = 0;
	while (argv[2][i] != '\0')
	{
        ft_send_bits(pid, argv[2][i]);
        pause();
		i++;
	}
	ft_send_bits(pid, '\n');
	pause();
	ft_printf("\033[1;34mMessage transmission complete!\033[0m\n");
	return (0);
}
