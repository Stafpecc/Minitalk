/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:55:16 by tarini            #+#    #+#             */
/*   Updated: 2025/02/12 16:00:22 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h> 
# include "../libft/includes/libft.h"

typedef struct s_message
{
	char	*msg;
	size_t	size;
	size_t	index;
	int		bit;
	int		sender_pid;
}	t_message;

#endif