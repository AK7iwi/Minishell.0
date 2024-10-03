/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:19:06 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/03 20:51:06 by mfeldman         ###   ########.fr       */
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

/* General erros */
# define ERROR_MALLOC			0x1

# define E_MALLOC	"Error\nMalloc fail error.\n"

/* Parsing error */

# define ERROR_ARG				0x1
# define ERROR_QUOTE			0x2
# define ERROR_OPERATOR			0x4
# define ERROR_REDIR			0x8
# define ERROR_PARAN			0x10

# define E_ARGS		"Error\nNo need argument bro.\n"
# define E_QUOTE	"Error\nClose you quotes.\n"
# define E_OPERATOR "Error\nInvalid use of operator.\n"
# define E_REDIR 	"Error\nInvalid use of redirection.\n"
# define E_PARAN 	"Error\nClose the paranthese bro.\n"

/* Exece errors */


//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_error
{
	uint8_t		error_gen;
	uint8_t		error_parsing;
	uint16_t	error_exec;
}	t_error;

//**********************************************//
//					ERROR   					//
//**********************************************//

/* msg_error.c*/
void 	free_error(t_error *error);
void	msg_error(t_error error);

#endif /* ERRORS_H */