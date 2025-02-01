/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:26 by tarini            #+#    #+#             */
/*   Updated: 2025/02/01 23:19:49 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_handler(int signal)
{
	static int	bit = 0;
	static int	i = 0;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("\033[1;36m%c\033[0m", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[1;91mError: Invalid arguments!\033[0m\n");
		ft_printf("\033[1;33mUsage: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[1;34m===== Server PID =====\033[0m\n");
	ft_printf("\033[1;36mPID\033[0m \033[1;92m->\033[0m %d\n", pid);
	ft_printf("\033[1;90mWaiting for a message...\033[0m\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
	return (0);
}
