/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:38:53 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:41:55 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	fill_square(t_data *data, int color, int i, int j)
{
	int	k;
	int	l;

	k = 0;
	while (k < data->mini_map_scale)
	{
		l = 0;
		while (l < data->mini_map_scale)
		{
			img_draw_pixel(&data->ray_to_draw, (i * data->mini_map_scale) + k,
				(j * data->mini_map_scale) + l, color);
			l++;
		}
		k++;
	}
}

int	draw_mini_map(t_data *data)
{
	int	color;
	int	x;
	int	y;

	x = 0;
	while (data->map[x] != NULL)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (data->map[x][y] == '1')
				color = 0x00FF0000;
			else
				color = 0x0000FF;
			fill_square(data, color, y, x);
			y++;
		}
		x++;
	}
	fill_square(data, 0x00FF00, (int)data->avatar_pos.x, \
		(int)data->avatar_pos.y);
	return (0);
}

void	img_draw_background(t_data *data)
{
	t_coor_int	current_position;

	ft_memset(&current_position, 0, sizeof(current_position));
	while (current_position.y < HEIGHT)
	{
		current_position.x = 0;
		while (current_position.x < WIDTH)
		{
			if (current_position.y <= HEIGHT / 2)
				img_draw_pixel(&data->ray_to_draw, current_position.x, \
				current_position.y, data->textures.ceiling_color);
			else
				img_draw_pixel(&data->ray_to_draw, current_position.x, \
				current_position.y, data->textures.floor_color);
			current_position.x++;
		}
		current_position.y++;
	}
}
