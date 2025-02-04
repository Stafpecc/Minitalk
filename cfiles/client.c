/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:24 by tarini            #+#    #+#             */
/*   Updated: 2025/02/04 19:54:33 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void send_bit(int pid, int bit)
{
    int ret;

    if (bit)
        ret = kill(pid, SIGUSR1);
    else
        ret = kill(pid, SIGUSR2);
    if (ret == -1)
    {
        ft_printf("\033[1;91mERROR: Failed to send signal!\033[0m\n");
        exit(EXIT_FAILURE);
    }
}

static void send_message(int pid, const char *message)
{
    size_t size_of_message;
    size_t i;

    size_of_message = ft_strlen(message);
    i = 15;
    while (i >= 0)
    {
        send_bit(pid, (size_of_message >> i) & 1);
        pause();
        i--;
    }
    while (*message)
    {
        unsigned char byte = *message++;
        i = 7;
        while (i >= 0)
        {
            send_bit(pid, (byte >> i) & 0x01);
            pause();
            i--;
        }
    }
    send_bit(pid, '\n');
}


int main(int argc, char **argv)
{
    int pid;

    if (argc != 3)
    {
        ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
        ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
        return (EXIT_FAILURE);
    }
    if (ft_atoi_only_num(argv[1], &pid) == FALSE)
    {
        ft_printf("\033[1;91mERROR: Invalid PID! Must be numeric.\033[0m\n");
        return (EXIT_FAILURE);
    }
    ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", pid);
    ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
    send_message(pid, argv[2]);
    ft_printf("\033[1;34mMessage transmission complete!\033[0m\n");
    return (EXIT_SUCCESS);
}
