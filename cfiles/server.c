/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:04:52 by tarini            #+#    #+#             */
/*   Updated: 2025/02/07 14:55:54 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_message g_msg = {NULL, 0, 0, 0};

static void reset_message(void)
{
	free(g_msg.msg);
	g_msg.msg = NULL;
	g_msg.size = 0;
	g_msg.index = 0;
	g_msg.bit = 0;
}

static void handle_signal(int signal, siginfo_t *info, void *context)
{
	static int byte = 0;

	(void)context;
	if (g_msg.size == 0)
	{
		if (signal == SIGUSR1)
		{
			ft_printf("je recois 1 mais ma size est 0\n");
			g_msg.size |= (1 << g_msg.bit);
		}
		g_msg.bit++;
		ft_printf("g: %d\n", g_msg.bit);
		if (g_msg.bit == 14)
		{
			ft_printf("Taille du message reçue: %d\n", g_msg.size / 8);
			g_msg.msg = malloc(g_msg.size / 8 + 1);
			if (!g_msg.msg)
				exit(EXIT_FAILURE);
			g_msg.msg[g_msg.size / 8] = '\0';
			g_msg.bit = 0;
		}
	}
	else
	{
		ft_printf("=========\n");
		if (signal == SIGUSR1)
		{
			ft_printf("je recois 1\n");
			byte |= (1 << g_msg.bit);
		}
		g_msg.bit++;
		ft_printf("g: %d\n", g_msg.bit);
		if (g_msg.bit == 8)
		{
			g_msg.msg[g_msg.index++] = byte;
			ft_printf("Caractère reçu: %c (index: %d)\n", byte, g_msg.index);
			byte = 0;
			g_msg.bit = 0;
			if (g_msg.index == g_msg.size / 8)
			{
				ft_printf("Message final reçu: %s\n", g_msg.msg);
				reset_message();
			}
		}
	}
	ft_printf("je kill 1\n");
	kill(info->si_pid, SIGUSR1);
	
}

static void setup_signals(void)
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static void display_server_pid(void)
{
	int pid = getpid();
	ft_printf("\033[1;34m===== Server PID =====\033[0m\n");
	ft_printf("\033[1;36mThe server's PID is:\033[0m \033[1;92m%d\033[0m\n", pid);
	ft_printf("\033[1;90mListening for incoming signals...\033[0m\n");
}

int main(void)
{
	display_server_pid();
	setup_signals();
	while (1)
		pause();
	return (0);
}
