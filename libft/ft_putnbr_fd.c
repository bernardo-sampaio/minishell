/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:12:00 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/19 13:13:04 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	number;

	number = n;
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		number *= -1;
	}
	if (number >= 0 && number <= 9)
	{
		ft_putchar_fd(number + '0', fd);
	}
	if (number > 9)
	{
		ft_putnbr_fd((number / 10), fd);
		ft_putnbr_fd((number % 10), fd);
	}
}
