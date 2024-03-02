/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:11:17 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/02 18:25:03 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	cal_wall_hit_x(t_ray *ray, double wall_hit)
{
	wall_hit -= floor(wall_hit);
	ray->wall_hit_x = (wall_hit * (double)ray->wall_txt.width);
	if ((ray->hit_side == 0 && ray->dir.x < 0) || 
			(ray->hit_side == 1 && ray->dir.y > 0))
			ray->wall_hit_x = ray->wall_txt.width - ray->wall_hit_x - 1;
}

void	values_for_texture(t_data *data, t_ray *ray)
{
	double wall_hit;
	
	if (ray->hit_side == 0)
	{
		ray->perp_dist =  ray->dist_to_side.y - ray->delta.y;
		wall_hit = data->avatar_pos.x + ray->perp_dist * ray->dir.x;
		if (ray->dir.y < 0)
			ray->wall_txt = data->textures.so;
		else
			ray->wall_txt = data->textures.no;
			
	}
	else
	{
		ray->perp_dist =  ray->dist_to_side.y - ray->delta.y;
		wall_hit = data->avatar_pos.y + ray->perp_dist * ray->dir.y;
		if (ray->dir.x < 0)
			ray->wall_txt = data->textures.we;//Add texture to data
		else
			ray->wall_txt = data->textures.ea;
			
	}
	cal_wall_hit_x(ray, wall_hit);
}

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

void	ray_cast(t_data *data, t_ray *rays, int x)
{
	double	ray_angle;
	
	ray_angle = data->facing_angle - FOV + x * rays->step_angle;
	rays->dir.x = -1 * cos(ray_angle);
	rays->dir.y = -1 * sin(ray_angle);
  	ray_cast_init(data, rays);
	dda_algo(data, rays);
	values_for_texture(data, rays);
	rays->perp_dist *= cos(ray_angle - data->facing_angle);
	rays->wall_height = (int)(HEIGHT / rays->perp_dist);
}