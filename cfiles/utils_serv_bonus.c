/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_serv_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:29:26 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 16:48:43 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	reset_handler_state(int *bit, int *i)
{
	*bit = 0;
	*i = 0;
}

void	handle_signal(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("\033[1;36m%c\033[0m", i);
		reset_handler_state(&bit, &i);
		kill(getppid(), SIGUSR1);
	}
}
