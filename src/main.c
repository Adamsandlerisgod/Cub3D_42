/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:04:19 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/01 16:48:41 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if ((x <= 0) || (x > img->width))
		return ;
	if ((y <= 0) || (y > img->height))
		return ;
	dst = img->addr + (y * img->line_length + x * 
			(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	draw_grid_vertical(t_img *img, int width)
// {
// 		for (int j = 0; img->width > (img->width/width) * j; j++)
// 		{
// 			for (int k = 0; k < img->height; k++)
// 				my_mlx_pixel_put(img, (img->width/width) * j, k, 0x000000FF);
// 		}
// }
// void	draw_grid_horizontal(t_img *img, int height)
// {
// 		for (int j = 0; img->height > (img->height/height) * j; j++)
// 		{
// 			for (int k = 0; k < img->width; k++)
// 				my_mlx_pixel_put(img, k, (img->height/height) * j, 0x000000FF);
// 		}
// }

// void	draw_grid(t_img *img, int width, int height)
// {
// 	draw_grid_horizontal(img, height);
// 	draw_grid_vertical(img, width);
// }

void	draw_avatar(t_data *data)
{
	int i;
	
	
	for (i = 0; i < 20; i++)
			my_mlx_pixel_put(&data->img, data->avatar_pos.x + i, data->avatar_pos.y, 0x00FF0000);
	for (i = 0; i < 20; i++)
			my_mlx_pixel_put(&data->img, data->avatar_pos.x + 20, data->avatar_pos.y + i, 0x00FF0000);
	for (i = 0; i < 20; i++)
			my_mlx_pixel_put(&data->img, data->avatar_pos.x + 20 - i, data->avatar_pos.y + 20, 0x00FF0000);
	for (i = 0; i < 20; i++)
			my_mlx_pixel_put(&data->img, data->avatar_pos.x, data->avatar_pos.y + i, 0x00FF0000);

}

void	moving(int key, t_data *data)
{
	if (key == KEY_LEFT)
		data->avatar_pos.x -= 20;
	if (key == KEY_RIGHT)
		data->avatar_pos.x += 20;
	if (key == KEY_UP)
		data->avatar_pos.y -= 20;
	if (key == KEY_DOWN)
		data->avatar_pos.y += 20;
		
}

int	key_hook(int key, t_data *data)
{
	printf("%d \n", key);
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->mlx.mlx, data->img.img);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		exit (0);
	}
	moving(key, data);
	mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, data->mlx.win_width , data->mlx.win_height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	// draw_grid(&data->img, 10, 10);
	draw_map(data);
	draw_avatar(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->img.img, 0, 0);
	return (-1);
}





int main(int ac, char **av)
{
	t_data	data;
	char *map[] =
	{
	"11111111",
	"10000001",
	"10010001",
	"10000001",
	"10000001",
	"10001001",
	"10000001",
	"11111111"
	};
	
	printf("waacka && %s && %d \n", av[0], ac);
	
	init_data(&data, map);
	
	data.mlx.mlx = mlx_init();
	data.mlx.mlx_win = mlx_new_window(data.mlx.mlx, data.mlx.win_width,	data.mlx.win_height, "Cub3D");
	// int i = 0;
	if (1)
	{
		data.img.img = mlx_new_image(data.mlx.mlx, data.mlx.win_width,
				data.mlx.win_height);
		data.img.addr = mlx_get_data_addr(data.img.img, 
				&data.img.bits_per_pixel, &data.img.line_length,
				&data.img.endian);
		 if ((mlx_key_hook(data.mlx.mlx_win, key_hook, &data)) != -1)
		{
			// draw_grid(&data.img, 10, 10);
			draw_map(&data);
			draw_avatar(&data);
		}
		mlx_put_image_to_window(data.mlx.mlx, data.mlx.mlx_win, data.img.img, 0, 0);
		mlx_loop(data.mlx.mlx);
	}
}