/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:24 by tarini            #+#    #+#             */
/*   Updated: 2025/02/07 14:50:10 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile int g_ack = 0;

static void send_bit(int pid, int bit)
{
    g_ack = 0;
    if (bit)
    {  
        ft_printf("Je kill 1 (bit 1)\n", pid);
        kill(pid, SIGUSR1);
    }
    else
    {
        ft_printf("Je kill 2 (bit 2)\n", pid);
        kill(pid, SIGUSR2);
    }
    while (!g_ack)
        ;
    //ft_printf("Ack bit: %d\n", bit);
}

static void send_message(int pid, const char *message)
{
    size_t size;
    int nb_bit;
    unsigned char byte;

    size = ft_strlen(message);
    ft_printf("taille du message: %d\n", size);
    nb_bit = 15;
    while (nb_bit >= 0)
    {
        //ft_printf("envoie du bit %d du message de taille: %d\n", (size >> nb_bit) & 1, size);
        send_bit(pid, (size >> nb_bit) & 1);
        nb_bit--;
    }
    while (*message)
    {
        byte = *message++;
        nb_bit = 7;
        ft_printf("=========\n");
        ft_printf("envoie: '%c' (0x%02X)\n", byte, byte);
        ft_printf("=========\n");
        while (nb_bit >= 0)
        {
            //ft_printf("Envoie du bit %d de 0x%02X\n", (byte >> nb_bit) & 1, byte);
            send_bit(pid, (byte >> nb_bit) & 1);
            nb_bit--;
        }
    }
    ft_printf("fin de signal\n");
    send_bit(pid, 0);
}

void recieved(int sig)
{
    if (sig == SIGUSR1)
    {
        g_ack = 1;
        ft_printf("j'ai recu l'ack de sig1\n");
    }
}

int main(int argc, char **argv)
{
    int server_pid;
    int client_pid;

    client_pid = getpid();
    if (argc != 3)
    {
        ft_printf("\033[1;91mERROR: Invalid arguments!\033[0m\n");
        ft_printf("\033[1;33mUsage: ./client <PID> <MESSAGE>\033[0m\n");
        return (EXIT_FAILURE);
    }
    signal(SIGUSR1, recieved);
    signal(SIGUSR2, recieved);
    if (ft_atoi_only_num(argv[1], &server_pid) == FALSE)
    {
        ft_printf("\033[1;91mERROR: Invalid PID! Must be numeric.\033[0m\n");
        return (EXIT_FAILURE);
    }
    ft_printf("\033[1;36m===== Client to PID %d =====\033[0m\n", client_pid);
    ft_printf("\033[1;32mStarting message transmission...\033[0m\n");
    send_message(server_pid, argv[2]);
    ft_printf("\033[1;34mMessage transmission complete!\033[0m\n");
    return EXIT_SUCCESS;
}
