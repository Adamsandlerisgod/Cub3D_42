/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:47:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/03 18:42:34 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_data(t_data *data, char **map)
{
	t_coor	avatar_pos = {1 , 1 };
	
	data->mlx.win_width = 1500;
	data->mlx.win_height = 1200;
	data->img.width = 1500;
	data->img.height = 1200;
	data->map = map;
	data->avatar_pos =	avatar_pos;	/*The coordinates that I get from your parsing*/
	data->avatar_pos.x = ((data->img.width/(8/*The map width*/)) * 1);
	data->avatar_pos.y = ((data->img.height/(8/*The map height*/)) * 1);
	
	// data->avatar_pos =	avatar_pos;	/*The coordinates that I get from your parsing*/
	// data->avatar_pos.x = 935;
	// data->avatar_pos.y = 600;
	printf("avatar pos x = %f, y = %f \n", data->avatar_pos.x, data->avatar_pos.y);
}