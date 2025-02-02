/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:24 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 16:53:24 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static void	send_bit(int pid, int bit)
{
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	send_char_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit(pid, (c & (0x01 << bit)) != 0);
		bit++;
	}
}

void	send_unicode_bit(int pid, wchar_t unicode_char)
{
	int	bit;

	bit = 0;
	while (bit < 32)
	{
		send_bit(pid, (unicode_char & (0x01 << bit)) != 0);
		bit++;
	}
}

static void	receive_confirmation(void)
{
	pause();
}

int	main(int argc, char **argv)
{
	int		pid;
	wchar_t	unicode_message[100];

	if (argc != 3)
	{
		ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
		ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", pid);
	ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
	if (ft_strchr(argv[2], 0x80))
	{
		mbstowcs(unicode_message, argv[2], 100);
		send_message_unicode(pid, unicode_message);
	}
	else
		send_message(pid, argv[2]);
	receive_confirmation();
	ft_printf("\033[1;34mMessage transmission complete!\033[0m\n");
	return (0);
}
