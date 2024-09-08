/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/08 17:34:15 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

//**********************************************//
//					INCLUDES					//
//**********************************************//

#include <stdint.h>

//**********************************************//
//					DEFINES						//
//**********************************************//

# define COLOR_RESET   "\x1b[0m"
# define COLOR_RED     "\x1b[31m"

# define ERROR_ARG				0x1

# define E_PARS_ARGS "Error\nNeed a single argument, a .cub map.\n"

/*Struct errors*/

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_error
{
	uint32_t	error_g;
}				t_error;


#endif /* ERRORS_H */