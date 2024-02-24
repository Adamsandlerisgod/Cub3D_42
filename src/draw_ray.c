/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/24 12:47:35 by whendrik         ###   ########.fr       */
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
static void	ray_cast_init(t_data *data, t_ray *rays)
{
	rays->map.x = (int)data->avatar_pos.x;
	rays->map.y = (int)data->avatar_pos.y;
	rays->delta.x = fabs(1 / rays->dir.x);
	rays->delta.y = fabs(1 / rays->dir.y);
	
}

static void	dda_algo(t_data *data, t_ray *rays)
{
	while (1)
	{
		if (rays->dist_to_side.x < rays->dist_to_side.y)
		{
			rays->dist_to_side.x += rays->delta.x;
			rays->map.x += rays->step.x;
			rays->hit_side = 0;
		}
		else
		{
			rays->dist_to_side.y += rays->delta.y;
			rays->map.y += rays->step.y;
			rays->hit_side = 1;
		}
		if (data->map[rays->map.y][rays->map.x] != '0')
			break ;
	}
}

static void	ray_cast(t_data *data, t_ray *rays, int x)
{
	double	ray_angle;
	
	ray_angle = data->facing_angle - FOV + x * rays->step_angle;
	rays->dir.x = -1 * cos(ray_angle);
	rays->dir.y = -1 * sin(ray_angle);
  	ray_cast_init(data, rays);
	dda_algo(data, rays);
	extra_val(data, rays);
	rays->perp_dist *= cos(ray_angle - data->facing_angle);
	rays->wall_height = (int)(HEIGHT / rays->perp_dist);
}

int draw_ray(t_data *data)
{
	//x and y start position
	// double posX = t_mapinfo->p_start_x;
	// double posY = t_mapinfo->p_start_y;
	double posX = 1;
	double posY = 1;
	assign_direction_hero(data, data->mapinfo.p_start_o);
	set_direction_of_step(data, &data->raycast);

	data->raycast.step_angle = (FOV * 2)/ WIDTH;
	double dirX = -1, dirY = 0; //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	int x;

	x= 0;
	while (x < WIDTH)
	{
	ray_cast(data, &data->raycast, x);
	//Draw the rays and walls
	 x++;
	}
}