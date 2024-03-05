/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/05 21:53:52 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"


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


void	draw_walls_ray(t_img *canvas, t_coor_int start_pos, t_coor_int end_pos, t_img wall_texture)
{
	unsigned int	pixel_color;
	int				texture_coordinate;
	int				line_height;
	int				tex_y;
	
	line_height = end_pos.y - start_pos.y;
	if (start_pos.y < 0)
		start_pos.y = 0;
	if (end_pos.y >= HEIGHT)
		end_pos.y = HEIGHT - 1;
	while (start_pos.y < end_pos.y)
	{
		texture_coordinate = (start_pos.y - HEIGHT / 2 + line_height / 2) 
			* wall_texture.height;
		tex_y = texture_coordinate / line_height;
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
	t_ray	rays_to_cast;
	//x and y start position
	// double posX = data->mapinfo.p_start_x;
	// double posY = data->mapinfo.p_start_y;
	set_direction_of_step(data, &rays_to_cast);

	rays_to_cast.step_angle = (FOV * 2)/ WIDTH;

	x = 0;
	while (x < WIDTH)
	{
	ray_cast(data, &rays_to_cast, x);
	//Draw the rays and walls
	draw_walls_ray(&data->ray_to_draw, (t_coor_int){x, (HEIGHT - rays_to_cast.wall_height) / 2}, 
			(t_coor_int){x, (HEIGHT + rays_to_cast.wall_height) / 2}, rays_to_cast.wall_txt);
	 x++;
	}
	return (0);
}