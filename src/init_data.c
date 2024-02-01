/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:47:14 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/01 16:48:56 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_data(t_data *data, char **map)
{
	data->avatar_pos.x = 750;
	data->avatar_pos.y = 600;
	data->mlx.win_width = 1500;
	data->mlx.win_height = 1200;
	data->img.width = 1500;
	data->img.height = 1200;
	data->map = map;
}