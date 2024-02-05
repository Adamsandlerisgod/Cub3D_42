/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:02:38 by justindaly        #+#    #+#             */
/*   Updated: 2024/02/02 17:09:47 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	err_msg(char *content, char *err_msg, int exit_code)
{
	ft_putstr_fd("cub3d: Error", 2);
	if (content)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(content, 2);
	}
	if (err_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_msg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (exit_code);
}
