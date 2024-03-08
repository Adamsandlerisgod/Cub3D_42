/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_cast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:11:17 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:44:08 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static void	cal_wall_hit_x(t_ray *ray, double wall_hit)
{
	wall_hit -= floor(wall_hit);
	ray->wall_hit_x = (wall_hit * (double)ray->wall_txt.width);
	if ((ray->hit_side == 0 && ray->dir.x < 0)
		|| (ray->hit_side == 1 && ray->dir.y > 0))
		ray->wall_hit_x = ray->wall_txt.width - ray->wall_hit_x - 1;
}

static void	values_for_texture(t_data *data, t_ray *ray)
{
	double	wall_hit;

	if (ray->hit_side != 0)
	{
		ray->perp_dist = ray->dist_to_side.y - ray->delta.y;
		wall_hit = data->avatar_pos.x + ray->perp_dist * ray->dir.x;
		if (ray->dir.y < 0)
			ray->wall_txt = data->textures.no;
		else
			ray->wall_txt = data->textures.so;
	}
	else
	{
		ray->perp_dist = ray->dist_to_side.x - ray->delta.x;
		wall_hit = data->avatar_pos.y + ray->perp_dist * ray->dir.y;
		if (ray->dir.x < 0)
			ray->wall_txt = data->textures.we;
		else
			ray->wall_txt = data->textures.ea;
	}
	cal_wall_hit_x(ray, wall_hit);
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
	assign_ray_cast(data, rays);
	dda_algo(data, rays);
	values_for_texture(data, rays);
	rays->perp_dist *= cos(ray_angle - data->facing_angle);
	rays->wall_height = (int)(HEIGHT / rays->perp_dist);
}
