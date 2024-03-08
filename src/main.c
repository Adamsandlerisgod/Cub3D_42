/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:04:19 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:49:27 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	main_loop(t_data *data)
{
	move_avatar(data);
	img_draw_background(data);
	draw_ray(data);
	draw_mini_map(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->ray_to_draw.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_mapinfo	mapinfo;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&mapinfo, sizeof(t_mapinfo));
	if (validate_cub(ac, av, &mapinfo) != SUCCESS)
		exit (1);
	if (!(init_program(&data, &mapinfo)))
		return (err_msg("", "Failed to initialize program", 0), 0);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.mlx_win, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.mlx.mlx_win, 5, 1L << 3, mouse_release, &data);
	mlx_loop_hook(data.mlx.mlx, main_loop, &data);
	mlx_loop(data.mlx.mlx);
}
