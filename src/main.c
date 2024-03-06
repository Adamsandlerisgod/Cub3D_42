/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:04:19 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/05 22:07:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"



void	moving(int key, t_data *data)
{
	if (key == KEY_ESC)
		kill_program(data);
	//MOVING
	if (key == KEY_A)
		data->avatar_pos.x -= 20;
	if (key == KEY_D)
		data->avatar_pos.x += 20;
	if (key == KEY_UP || key == KEY_W)
		data->avatar_pos.y -= 20;
	if (key == KEY_DOWN || key == KEY_S)
		data->avatar_pos.y += 20;
	//ROTATING
	if (key == KEY_LEFT)
		data->facing_angle -= 0.1;
	if (key == KEY_RIGHT)
		data->facing_angle += 0.1;
		
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		kill_program(data);
	moving(key, data);
	mlx_destroy_image(data->mlx.mlx, data->ray_to_draw.img);
	data->ray_to_draw.img = mlx_new_image(data->mlx.mlx, data->mlx.win_width , data->mlx.win_height);
	data->ray_to_draw.addr = mlx_get_data_addr(data->ray_to_draw.img, &data->ray_to_draw.bits_per_pixel,
			&data->ray_to_draw.line_length, &data->ray_to_draw.endian);
	// draw_grid(&data->ray_to_draw, 10, 10);
	// draw_map(data);
	// draw_avatar(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->ray_to_draw.img, 0, 0);
	return (-1);
}

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
}

int	kill_program(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

bool	init_program(t_data *data, t_mapinfo *mapinfo)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		return (FALSE);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (data->mlx.mlx_win == NULL)
		return (FALSE);
	if (init_img(&data->mlx.mlx, &data->ray_to_draw, WIDTH, HEIGHT))
		return (FALSE);
	mlx_hook(data->mlx.mlx_win, 17, 0, kill_program, data);
	return (TRUE);
}

int main_loop(t_data *data)
{
	//move avatar function
	img_draw_background(data);
	draw_ray(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		 data->ray_to_draw.img, 0, 0);
	
}


int main(int ac, char **av)
{
	t_data	data;
	t_mapinfo	mapinfo;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&mapinfo, sizeof(t_mapinfo));
	if (validate_cub(ac, av, &mapinfo))
		return (0);
	init_assign_data(&data, &mapinfo);
	if (!(init_program(&data)))
		return(err_msg("" ,"Failed to initialize program", 0), 0);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, key_press, &data);
	// mlx_hook(data.mlx.mlx_win, 3, 1L << 1, key_release, &data);
	//Need to write for key_release
	mlx_loop_hook(data.mlx.mlx, main_loop, &data);
	mlx_loop(data.mlx.mlx);
}