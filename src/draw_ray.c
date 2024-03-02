/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/29 21:18:43 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"



int draw_ray(t_data *data)
{
	int x;
	t_ray	ray;
	//x and y start position
	// double posX = t_mapinfo->p_start_x;
	// double posY = t_mapinfo->p_start_y;
	double posX = 1;
	double posY = 1;
	assign_direction_hero(data, data->mapinfo.p_start_o);
	set_direction_of_step(data, &data->raycast);

	data->raycast.step_angle = (FOV * 2)/ WIDTH;

	x = 0;
	while (x < WIDTH)
	{
	ray_cast(data, &ray, x);
	//Draw the rays and walls
	draw_ray_and_walls(data, &ray, x);
	 x++;
	}
}