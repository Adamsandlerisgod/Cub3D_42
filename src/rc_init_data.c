/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:47:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/06 20:54:14 by whendrik         ###   ########.fr       */
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

t_img	text_assign(t_data *data, char *path, int width, int height)
{
	t_img	texture;

	texture.width = width;
	texture.height = height;
	printf("path = %s\n", path);
	texture.img = mlx_xpm_file_to_image(data->mlx.mlx, path,
		&texture.width, &texture.height);
	printf("texture.img = %p\n", texture.img);
	if (texture.img == NULL)
		return (texture);
	printf("texture.img = %p\n", texture.img);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
		&texture.line_length, &texture.endian);
	return (texture);
}

static bool assign_texture(t_data *data, t_mapinfo *map)
{
	data->textures.no = text_assign(data, map->no_path, 64, 64); 
	if (data->textures.no.img == NULL)
		return (FALSE);
	data->textures.so = text_assign(data, map->so_path, 64, 64); 
	if (data->textures.so.img == NULL)
		return (FALSE);
	data->textures.ea = text_assign(data, map->ea_path, 64, 64); 
	if (data->textures.so.img == NULL)
		return (FALSE);
	data->textures.we = text_assign(data, map->we_path, 64, 64); 
	if (data->textures.we.img == NULL)
		return (FALSE);
	return (TRUE);
}	

bool	init_assign_data(t_data *data, t_mapinfo *map)
{

	init_data(data);
	printf("here\n");
	if (assign_texture(data, map) == FALSE)
		return (FALSE);
	printf("thehere\n");
	data->mlx.win_width = WIDTH;
	data->mlx.win_height = HEIGHT;
	data->ray_to_draw.width = WIDTH;
	data->ray_to_draw.height = HEIGHT;
	data->map = map->map;
	data->avatar_pos.x = ((data->ray_to_draw.width/(map->width)) * map->p_start_x);
	data->avatar_pos.y = ((data->ray_to_draw.height/(map->height)) * map->p_start_y);
	assign_direction_hero(data, map->p_start_o);
	return (TRUE);
}