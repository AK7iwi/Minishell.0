/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:41:32 by diguler           #+#    #+#             */
/*   Updated: 2023/11/08 19:10:28 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	i = 0;
	while (dst[i] && i < size)
	{
		i++;
	}
	d_len = i;
	while ((src[i - d_len] && i + 1 < size))
	{
		dst[i] = src[i - d_len];
		i++;
	}
	if (d_len < size)
		dst[i] = '\0';
	return (d_len + s_len);
}
