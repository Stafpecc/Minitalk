/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:53:44 by tarini            #+#    #+#             */
/*   Updated: 2025/02/04 22:10:36 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h> 
# include <stdlib.h> 
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include "../libft/includes/libft.h"

typedef struct s_message
{
    char    *msg;
    size_t  size;
    size_t  index;
    int     bit;
}   t_message;

extern t_message message;

#endif
