/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:48:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/05 21:54:01 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	img_draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	// if ((x <= 0) || (x > img->width))
	// 	return ;
	// if ((y <= 0) || (y > img->height))
	// 	return ;
	dst = img->addr + (y * img->line_length + x * 
			(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_img *img, int x, int y)
{
	void	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)dst);
}