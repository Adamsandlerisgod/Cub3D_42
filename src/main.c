/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:04:19 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/06 22:34:15 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"


static bool	init_img(void *mlx, t_img *ray_to_draw, int width, int height)
{
	ray_to_draw->img = mlx_new_image(mlx, width, height);
	if (ray_to_draw->img == NULL)
		return (FALSE);
	ray_to_draw->addr = mlx_get_data_addr(ray_to_draw->img, &ray_to_draw->bits_per_pixel,
			&ray_to_draw->line_length, &ray_to_draw->endian);
	if (ray_to_draw->addr == NULL)
		return (FALSE);
	ray_to_draw->width = width;
	ray_to_draw->height = height;
	return (TRUE);
}

int	kill_program(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
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

void init_data(t_data *data)
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

bool	init_program(t_data *data, t_mapinfo *mapinfo)
{
	init_data(data);
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		return (FALSE);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (data->mlx.mlx_win == NULL)
		return (FALSE);
	if (!(init_img(&data->mlx.mlx, &data->ray_to_draw, WIDTH, HEIGHT)))
		return (FALSE);
	if (!(assign_data(data, mapinfo)))
		return(err_msg("", "Failed to assign data", 0), 0);
	mlx_hook(data->mlx.mlx_win, 17, 0, kill_program, data);
	return (TRUE);
}

int main_loop(t_data *data)
{
	//move avatar function
	printf("main loop\n");
	img_draw_background(data);
	printf("draw background\n");
	draw_ray(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		 data->ray_to_draw.img, 0, 0);
	return (0);
}



int main(int ac, char **av)
{
	t_data	data;
	t_mapinfo	mapinfo;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&mapinfo, sizeof(t_mapinfo));
	if (validate_cub(ac, av, &mapinfo) != SUCCESS)
		return (0);
	if (!(init_program(&data, &mapinfo)))
		return(err_msg("" ,"Failed to initialize program", 0), 0);
	printf("init program\n");
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.mlx_win, 3, 1L << 1, key_release, &data);
	printf("post-key press/release\n");
	mlx_loop_hook(data.mlx.mlx, main_loop, &data);
	mlx_loop(data.mlx.mlx);
}
//Create a function to init avatar position and direction properly and as a flaot