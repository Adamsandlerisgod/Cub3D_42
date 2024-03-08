/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_assign_raycast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:46:15 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:46:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static void	set_direction_of_step(t_data *data, t_ray *rays)
{
	if (rays->dir.x < 0)
	{
		rays->step.x = -1;
		rays->dist_to_side.x = (data->avatar_pos.x - rays->map.x) \
		* rays->delta.x;
	}
	else
	{
		rays->step.x = 1;
		rays->dist_to_side.x = (rays->map.x + 1.0 - data->avatar_pos.x) \
		* rays->delta.x;
	}
	if (rays->dir.y < 0)
	{
		rays->step.y = -1;
		rays->dist_to_side.y = (data->avatar_pos.y - rays->map.y) \
		* rays->delta.y;
	}
	else
	{
		rays->step.y = 1;
		rays->dist_to_side.y = (rays->map.y + 1.0 - data->avatar_pos.y) \
			* rays->delta.y;
	}
}

void	assign_ray_cast(t_data *data, t_ray *rays)
{
	rays->map.x = (int)data->avatar_pos.x;
	rays->map.y = (int)data->avatar_pos.y;
	rays->delta.x = fabs(1 / rays->dir.x);
	rays->delta.y = fabs(1 / rays->dir.y);
	set_direction_of_step(data, rays);
}
