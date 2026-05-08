/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 07:54:09 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/16 17:09:30 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num == 0 || size == 0)
		return (malloc(1));
	if (num > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(num * size);
	if (ptr)
		ft_bzero(ptr, num * size);
	return (ptr);
}
