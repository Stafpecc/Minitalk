/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:24 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 16:20:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_bit(int pid, int bit)
{
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

static void	send_char_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit(pid, (c & (0x01 << bit)) != 0);
		bit++;
	}
}

static void	send_message(int pid, const char *message)
{
	while (*message)
	{
		send_char_bits(pid, *message);
		message++;
	}
	send_char_bits(pid, '\n');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
		ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", pid);
	ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
	send_message(pid, argv[2]);
	ft_printf("\033[1;34mMessage transmission complete!\033[0m\n");
	return (0);
}
