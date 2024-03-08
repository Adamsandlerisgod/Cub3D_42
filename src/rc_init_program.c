/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_init_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:26:25 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:31:42 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static bool	init_img(t_data *data, t_img *ray_to_draw, int width, int height)
{
	ray_to_draw->img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (ray_to_draw->img == NULL)
		return (FALSE);
	ray_to_draw->addr = mlx_get_data_addr(ray_to_draw->img, \
		&ray_to_draw->bits_per_pixel, &ray_to_draw->line_length, \
		&ray_to_draw->endian);
	if (ray_to_draw->addr == NULL)
		return (FALSE);
	ray_to_draw->width = width;
	ray_to_draw->height = height;
	return (TRUE);
}

static void	init_texture(t_textures *texture, t_mapinfo *mapinfo)
{
	texture->no.img = NULL;
	texture->so.img = NULL;
	texture->we.img = NULL;
	texture->ea.img = NULL;
	texture->floor_color = mapinfo->f_color_int;
	texture->ceiling_color = mapinfo->c_color_int;
}

static void	init_data(t_data *data, t_mapinfo *mapinfo)
{
	data->mlx.mlx = NULL;
	data->mlx.mlx_win = NULL;
	data->ray_to_draw.img = NULL;
	data->map = NULL;
	init_texture(&data->textures, mapinfo);
	data->avatar_pos.x = -1;
	data->avatar_pos.y = -1;
	data->facing_angle = -1;
	data->mini_map_scale = 5 + (28 / mapinfo->height + 28 / mapinfo->width);
}

bool	init_program(t_data *data, t_mapinfo *mapinfo)
{
	init_data(data, mapinfo);
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		return (FALSE);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (data->mlx.mlx_win == NULL)
		return (FALSE);
	if (!(init_img(data, &data->ray_to_draw, WIDTH, HEIGHT)))
		return (FALSE);
	if (!(assign_data(data, mapinfo)))
		return (err_msg("", "Failed to assign data", 0), 0);
	mlx_hook(data->mlx.mlx_win, 17, 0, kill_program, data);
	return (TRUE);
}
