/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:47:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/05 21:41:44 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static void	assign_direction_hero(t_data *data, char dir)
{
	if (dir == 'N')
		data->facing_angle = PI / 2;
	else if (dir == 'S')
		data->facing_angle = 3 * PI / 2;
	else if (dir == 'W')
		data->facing_angle = 0;
	else if (dir == 'E')
		data->facing_angle = PI;
}

static void	init_texture(t_textures *texture)
{
	texture->no.img = NULL;
	texture->so.img = NULL;
	texture->we.img = NULL;
	texture->ea.img = NULL;
	texture->floor_color = 0;
	texture->ceiling_color = 0;
}

static void init_data(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.mlx_win = NULL;
	data->ray_to_draw.img = NULL;
	data->map = NULL;
	init_texture(&data->textures);
	data->avatar_pos.x = -1;
	data->avatar_pos.y = -1;
	data->facing_angle = -1;
}

void	init_assign_data(t_data *data, t_mapinfo *map)
{
	init_data(data);
	data->mlx.win_width = WIDTH;
	data->mlx.win_height = HEIGHT;
	data->ray_to_draw.width = WIDTH;
	data->ray_to_draw.height = HEIGHT;
	data->map = map->map;
	data->avatar_pos.x = ((data->ray_to_draw.width/(map->width)) * map->p_start_x);
	data->avatar_pos.y = ((data->ray_to_draw.height/(map->height)) * map->p_start_y);
	assign_direction_hero(data, map->p_start_o);
}