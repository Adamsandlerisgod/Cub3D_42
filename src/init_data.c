/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:47:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/01 14:41:55 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_data(t_data *data, t_mapinfo *map)
{
	data->mlx.win_width = 1500;
	data->mlx.win_height = 1200;
	data->img.width = 1500;
	data->img.height = 1200;
	data->map = map->map;
	data->avatar_pos.x = ((data->img.width/(map->width)) * map->p_start_x);
	data->avatar_pos.y = ((data->img.height/(map->height)) * map->p_start_y);
	// data->avatar_pos =	avatar_pos;	/*The coordinates that I get from your parsing*/
	
	// data->avatar_pos =	avatar_pos;	/*The coordinates that I get from your parsing*/
	// data->avatar_pos.x = 935;
	// data->avatar_pos.y = 600;
	printf("avatar pos x = %d, y = %d \n", data->avatar_pos.x, data->avatar_pos.y);
}