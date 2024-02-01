/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:29:23 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/01 17:01:43 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

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

void	fill_square( t_img *img, int width, int height, int color, int i, int j)
{
	printf("we are in fill square|| width = %d || height = %d \n", width, height);
	for (int k = 0; width > k; k++)
	{
		for (int l = 0; l < height; l++)
			my_mlx_pixel_put(img, (width * i) + k, (j * height) + l, color);
	}
}



int		draw_map(t_data	*data)
{
	int mapX = 8;
	int mapY = 8;
	// int mapS = 64;
	int x = 0;
	int y = 0;


	char **map = data->map;

	printf("We are here\n");
	while (x < mapX)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			printf("coor map = (%d, %d) = %c\n", y , x, map[y][x]);
			if (map[y][x] == '1')
				fill_square(&data->img, data->img.width/mapX - 5,
					data->img.height/mapY - 5, 0x00FF0000, y, x);
			else if (map[y][x] == '0')
				fill_square(&data->img, data->img.width/mapX - 5,
					data->img.height/mapY - 5, 0x0000FF, y, x);
			y++;
		}
		x++;	
	}
	return (0);
}