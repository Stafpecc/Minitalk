/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:31:33 by tarini            #+#    #+#             */
/*   Updated: 2025/02/02 16:37:28 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "../libft/includes/libft.h"

void	send_message(int pid, const char *message);
void	send_message_unicode(int pid, const wchar_t *message);
void	reset_handler_state(int *bit, int *i);
void	handle_signal(int signal);
void	send_char_bits(int pid, char c);
void	send_unicode_bit(int pid, wchar_t unicode_char);

#endif