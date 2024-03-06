/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:29:23 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/05 21:53:30 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

// // void	draw_grid_vertical(t_img *img, int width)
// // {
// // 		for (int j = 0; img->width > (img->width/width) * j; j++)
// // 		{
// // 			for (int k = 0; k < img->height; k++)
// // 				img_draw_pixel(img, (img->width/width) * j, k, 0x000000FF);
// // 		}
// // }
// // void	draw_grid_horizontal(t_img *img, int height)
// // {
// // 		for (int j = 0; img->height > (img->height/height) * j; j++)
// // 		{
// // 			for (int k = 0; k < img->width; k++)
// // 				img_draw_pixel(img, k, (img->height/height) * j, 0x000000FF);
// // 		}
// // }

// // void	draw_grid(t_img *img, int width, int height)
// // {
// // 	draw_grid_horizontal(img, height);
// // 	draw_grid_vertical(img, width);
// // }

// void	fill_square( t_img *img, int width, int height, int color, int i, int j)
// {
// 	printf("we are in fill square|| width = %d || height = %d \n", width, height);
// 	for (int k = 0; width > k; k++)
// 	{
// 		for (int l = 0; l < height; l++)
// 			img_draw_pixel(img, (width * i) + k, (j * height) + l, color);
// 	}
// }



// int		draw_map(t_data	*data)
// {
// 	int mapX = 8;
// 	int mapY = 8;
// 	// int mapS = 64;
// 	int x = 0;
// 	int y = 0;


// 	char **map = data->map;

// 	printf("We are here\n");
// 	while (x < mapX)
// 	{
// 		y = 0;
// 		while (map[x][y] != '\0')
// 		{
// 			printf("coor map = (%d, %d) = %c\n", y , x, map[y][x]);
// 			if (map[x][y] == '1')
// 				fill_square(&data->img, data->img.width/mapX,
// 					data->img.height/mapY, 0x00FF0000, y, x);
// 			else
// 				fill_square(&data->img, data->img.width/mapX,
// 					data->img.height/mapY, 0x0000FF, y, x);
// 			y++;
// 		}
// 		x++;	
// 	}
// 	return (0);
// }

// Draw the background on the canvas with ceiling and floor textures
void img_draw_background(t_data *data)
{
    // Initialize variable to store the current position
    t_coor_int current_position;

    // Set all bytes of the position variable to 0
    ft_memset(&current_position, 0, sizeof(current_position));

    // Loop through each row of the canvas
    while (current_position.y < HEIGHT)
    {
        // Initialize the position's x-coordinate to 0
        current_position.x = 0;

        // Loop through each column of the canvas
        while (current_position.x < WIDTH)
        {
            // Check if the current pixel is above or at the middle of the canvas
            if (current_position.y <= HEIGHT / 2)
                // Draw the pixel with the ceiling texture color
                img_draw_pixel(&data->ray_to_draw, current_position.x, current_position.y, data->textures.ceiling_color);
            else
                // Draw the pixel with the floor texture color
                img_draw_pixel(&data->ray_to_draw, current_position.x, current_position.y, data->textures.floor_color);

            // Move to the next column
            current_position.x++;
        }

        // Move to the next row
        current_position.y++;
    }
}