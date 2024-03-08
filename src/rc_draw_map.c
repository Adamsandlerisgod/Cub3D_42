/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:29:23 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/06 17:03:25 by whendrik         ###   ########.fr       */
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

void fill_square(t_data *data, int color, int i, int j) 
{
    int k;
    int l;

    k = 0;
    l = 0;
    while(k < data->mini_map_scale)
     {
        l = 0;
        while(l < data->mini_map_scale)
        {
            img_draw_pixel(&data->ray_to_draw, (i * data->mini_map_scale) + k,
                (j * data->mini_map_scale) + l, color);
            l++;
        }
        k++;
    }
}


int draw_mini_map(t_data *data) {
    int color;
    int x;
    int y;

    x = 0;
    while (data->map[x] != NULL) { // Loop through each row in the map
        y = 0;
        while (data->map[x][y] != '\0') { // Loop through each column in the current row
            if (data->map[x][y] == '1') {
                color = 0x00FF0000; // Red color for walls ('1')
            } else {
                color = 0x0000FF; // Blue color for empty space
            }
            fill_square(data, color, y, x);
            y++;
        }
        x++;
    }
    fill_square(data, 0x00FF00, (int)data->avatar_pos.x , (int)data->avatar_pos.y);
    return (0);
}

void img_draw_background(t_data *data)
{
    t_coor_int current_position;

    ft_memset(&current_position, 0, sizeof(current_position));

    while (current_position.y < HEIGHT)
    {
        current_position.x = 0;
        while (current_position.x < WIDTH)
        {
            if (current_position.y <= HEIGHT / 2)
                img_draw_pixel(&data->ray_to_draw, current_position.x, current_position.y, data->textures.ceiling_color);
            else
                img_draw_pixel(&data->ray_to_draw, current_position.x, current_position.y, data->textures.floor_color);
            current_position.x++;
        }
        current_position.y++;
    }
}