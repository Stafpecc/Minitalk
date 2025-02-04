/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:44 by tarini            #+#    #+#             */
/*   Updated: 2025/02/04 19:56:21 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h> 
# include <stdlib.h> 
# include <unistd.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef struct s_message_data
{
    int size;
    int bit;
    int index;
    char *message;
} t_message_data;

extern t_message_data message_data;

#endif
