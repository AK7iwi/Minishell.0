/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/30 10:56:25 by mfeldman         ###   ########.fr       */
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
# define ERROR_OPERATOR			0x8
# define ERROR_REDIR			0x10
# define ERROR_PARAN			0x20

# define E_MALLOC	"Error\nMalloc fail error.\n"
# define E_ARGS		"Error\nNo need argument bro.\n"
# define E_QUOTE	"Error\nClose you quotes.\n"
# define E_OPERATOR "Error\nInvalid use of operator.\n"
# define E_REDIR 	"Error\nInvalid use of redirection.\n"
# define E_PARAN 	"Error\nClose the paranthese bro.\n"

/*Struct errors*/

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_error
{
	uint32_t	error_g;
}	t_error;

//**********************************************//
//					ERROR   					//
//**********************************************//

/* msg_error.c*/
void 	free_error(t_error *error);
void	msg_error(t_error error);

#endif /* ERRORS_H */