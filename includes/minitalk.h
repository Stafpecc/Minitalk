/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:44 by tarini            #+#    #+#             */
/*   Updated: 2025/02/12 15:58:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

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
