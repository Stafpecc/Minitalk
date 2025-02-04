/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:21:25 by tarini            #+#    #+#             */
/*   Updated: 2025/02/04 19:56:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_message_data message_data = {0};

static void reset_handler_state(void)
{
    message_data.bit = 0;
}

static void handle_signal(int signal, siginfo_t *info, void *context)
{
    static int byte_value;

    (void)context;
    if (message_data.size == 0)
    {
        if (signal == SIGUSR1)
            message_data.size |= (0x01 << message_data.bit);
    }
    else
    {
        if (signal == SIGUSR1)
            byte_value |= (0x01 << message_data.bit);
        message_data.bit++;
        
        if (message_data.bit == 8)
        {
            if (message_data.index < message_data.size)
            {
                message_data.message[message_data.index++] = byte_value;
                byte_value = 0;
            }
            else
            {
                message_data.message[message_data.index] = '\0';
                ft_printf("\033[1;36mMessage reçu: %s\033[0m\n", message_data.message);
                free(message_data.message);
                message_data.size = 0;
                message_data.index = 0;
            }
            reset_handler_state();
        }
    }

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
    int pid;

    pid = getpid();
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
