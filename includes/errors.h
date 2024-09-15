/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 17:57:11 by mfeldman         ###   ########.fr       */
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

# define ERROR_MALLOC			0x1
# define ERROR_ARG				0x2
# define ERROR_QUOTE			0x4
# define ERROR_PIPE				0x8
# define ERROR_REDIR			0x10

# define E_MALLOC	"Error\nMalloc fail error.\n"
# define E_ARGS		"Error\nNo need argument.\n"
# define E_QUOTE	"Error\nClose you quotes.\n"
# define E_PIPE 	"Error\nInvalid use of pipe.\n"
# define E_REDIR 	"Error\ninvalid use of redirection.\n"

/*Struct errors*/

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_error
{
	uint32_t	error_g;
}	t_error;

#endif /* ERRORS_H */