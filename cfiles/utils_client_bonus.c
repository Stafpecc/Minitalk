/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:47:56 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 16:48:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	send_message(int pid, const char *message)
{
	while (*message)
	{
		send_char_bits(pid, *message);
		message++;
	}
	send_char_bits(pid, '\n');
}

void	send_message_unicode(int pid, const wchar_t *message)
{
	while (*message)
	{
		send_unicode_bit(pid, *message);
		message++;
	}
	send_unicode_bit(pid, L'\n');
}