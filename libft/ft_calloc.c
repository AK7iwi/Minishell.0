/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:46:02 by diguler           #+#    #+#             */
/*   Updated: 2023/11/14 17:35:25 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int				x;
	unsigned char	*dest;

	dest = 0;
	x = count * size;
	if (size && x / size != count)
		return (NULL);
	dest = malloc(x);
	if (!dest)
		return (NULL);
	ft_bzero(dest, x);
	return ((void *)dest);
}
