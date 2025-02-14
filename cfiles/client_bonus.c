/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:01:13 by tarini            #+#    #+#             */
/*   Updated: 2025/02/13 18:52:28 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile int	g_ack = 0;

static void	received(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("\033[1;32mMessage received by server!\033[0m\n");
		exit(EXIT_SUCCESS);
	}
}

static void	ft_send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			usleep(100);
		bit++;
	}
}

static void	ft_send_message(int pid, const char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		ft_send_char(pid, message[i]);
		i++;
	}
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
		ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
		return (EXIT_FAILURE);
	}
	if (ft_atoi_only_num(argv[1], &server_pid) == FALSE)
	{
		ft_printf("\033[1;91mERROR: Invalid PID! Must be numeric.\033[0m\n");
		return (EXIT_FAILURE);
	}
	signal(SIGUSR1, received);
	signal(SIGUSR2, received);
	ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", server_pid);
	ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
	ft_send_message(server_pid, argv[2]);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
