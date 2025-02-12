/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:53:14 by tarini            #+#    #+#             */
/*   Updated: 2025/02/12 16:02:51 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_message	g_msg = {NULL, 0, 0, 0, 0};

static void	reset_message(void)
{
	free(g_msg.msg);
	g_msg.msg = NULL;
	g_msg.size = 0;
	g_msg.index = 0;
	g_msg.bit = 0;
	g_msg.sender_pid = 0;
}

static void	ft_process_signal(int signal, siginfo_t *info)
{
	if (g_msg.sender_pid == 0)
		g_msg.sender_pid = info->si_pid;
	else if (g_msg.sender_pid != info->si_pid)
		return ;
	if (g_msg.msg == NULL)
	{
		g_msg.size = 1024;
		g_msg.msg = ft_calloc(g_msg.size, sizeof(char));
		if (!g_msg.msg)
			return ;
	}
	if (signal == SIGUSR1)
		g_msg.msg[g_msg.index] |= (1 << g_msg.bit);
	g_msg.bit++;
}

static void	ft_manage_message(void)
{
	char	*new_msg;

	if (g_msg.bit == 8)
	{
		g_msg.bit = 0;
		g_msg.index++;
		if (g_msg.index >= g_msg.size - 1)
		{
			new_msg = ft_realloc(g_msg.msg, g_msg.size + 1024);
			if (!new_msg)
				return (reset_message());
			g_msg.msg = new_msg;
			g_msg.size += 1024;
		}
		if (g_msg.msg[g_msg.index - 1] == '\0')
		{
			ft_printf("%s\n", g_msg.msg);
			kill(g_msg.sender_pid, SIGUSR2);
			return (reset_message());
		}
	}
	kill(g_msg.sender_pid, SIGUSR1);
}

static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	ft_process_signal(signal, info);
	ft_manage_message();
}

int	main(void)
{
	struct sigaction	signal;

	ft_printf("\033[1;34m===== Server PID =====\033[0m\n");
	ft_printf("\033[1;36mThe server's PID is:\033[0m \033[1;92m%d\033[0m\n", \
		getpid());
	ft_printf("\033[1;90mListening for incoming signals...\033[0m\n");
	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = ft_handler;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
