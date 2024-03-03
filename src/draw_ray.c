/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/03 17:52:56 by whendrik         ###   ########.fr       */
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

static void set_direction_of_step(t_data *data, t_ray *rays)
{
  if (rays->dir.x < 0)
	{
		rays->step.x = -1;
		rays->dist_to_side.x = (data->avatar_pos.x - rays->map.x) * rays->delta.x;
	}
	else
	{
		rays->step.x = 1;
		rays->dist_to_side.x = (rays->map.x + 1.0 - data->avatar_pos.x) * rays->delta.x;
	}
	if (rays->dir.y < 0)
	{
		rays->step.y = -1;
		rays->dist_to_side.y = (data->avatar_pos.y - rays->map.y) * rays->delta.y;
	}
	else
	{
		rays->step.y = 1;
		rays->dist_to_side.y = (rays->map.y + 1.0 - data->avatar_pos.y) * rays->delta.y;
	}
}

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
                img_draw_pixel(&data->rc, current_position.x, current_position.y, data->texture.ceiling);
            else
                // Draw the pixel with the floor texture color
                img_draw_pixel(&data->rc, current_position.x, current_position.y, data->texture.floor);

            // Move to the next column
            current_position.x++;
        }

        // Move to the next row
        current_position.y++;
    }
}

void	img_draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_walls_ray(t_img *canvas, t_coor_int start_pos, t_coor_int end_pos, t_img wall_texture)
{
	unsigned int	pixel_color;
	int				texture_coordinate;
	int				line_height;

	line_height = end_pos.y - start_pos.y;
	if (start_pos.y < 0)
		start_pos.y = 0;
	if (end_pos.y >= HEIGHT)
		end_pos.y = HEIGHT - 1;
	while (start_pos.y < end_pos.y)
	{
		texture_coordinate = (start_pos.y - HEIGHT / 2 + line_height / 2) * wall_texture.tex_h;
		int tex_y = texture_coordinate / line_height;
		if (tex_y >= wall_texture.height)
			tex_y = wall_texture.height - 1;
		if (tex_y < 0)
			tex_y = 0;
		pixel_color = get_pixel_color(&wall_texture, end_pos.x, tex_y);
		img_draw_pixel(canvas, start_pos.x, start_pos.y, pixel_color);
		start_pos.y++;
	}
}

int draw_ray(t_data *data)
{
	int x;
	t_ray	ray;
	//x and y start position
	double posX = data->mapinfo.p_start_x;
	double posY = data->mapinfo.p_start_y;
	set_direction_of_step(data, &data->raycast);

	data->raycast.step_angle = (FOV * 2)/ WIDTH;

	x = 0;
	while (x < WIDTH)
	{
	ray_cast(data, &ray, x);
	//Draw the rays and walls
	draw_walls_ray(&data->img, (t_coor_int){x, (HEIGHT - ray.wall_height) / 2}, 
			(t_coor_int){x, (HEIGHT + ray.wall_height) / 2}, ray.wall_txt);
	 x++;
	}
	return (0);
}