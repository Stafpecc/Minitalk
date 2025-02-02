/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:26 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 15:50:43 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void reset_handler_state(int *bit, int *i)
{
    *bit = 0;
    *i = 0;
}

static void handle_signal(int signal)
{
    static int bit = 0;
    static int i = 0;

    if (signal == SIGUSR1)
        i |= (0x01 << bit);
    bit++;

    if (bit == 8)
    {
        ft_printf("\033[1;36m%c\033[0m", i);
        reset_handler_state(&bit, &i);
    }
}

static void setup_signals(void)
{
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
}

static void display_server_pid(void)
{
    int pid = getpid();
    ft_printf("\033[1;34m===== Server PID =====\033[0m\n");
    ft_printf("\033[1;36mThe server's PID is:\033[0m \033[1;92m%d\033[0m\n", pid);
    ft_printf("\033[1;90mListening for incoming signals...\033[0m\n");
}

int main(int argc, char **argv)
{
    (void)argv;

    if (argc != 1)
    {
        ft_printf("\033[1;91mError: Invalid arguments!\033[0m\n");
        ft_printf("\033[1;33mUsage: ./server\033[0m\n");
        return (0);
    }

    display_server_pid();
    setup_signals();

    while (1)
    {
        pause();
    }

    return (0);
}

