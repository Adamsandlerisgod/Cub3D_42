/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:57:19 by justindaly        #+#    #+#             */
/*   Updated: 2024/02/23 15:36:47 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'W' || c == 'E' || c == ' ');
}

int	is_player_start(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_valid_player_pos(t_mapinfo *mapinfo)
{
	return ((mapinfo->p_start_x > 0 && mapinfo->p_start_x < \
			(mapinfo->width - 1)) && mapinfo->p_start_y > 0 \
			&& mapinfo->p_start_y < (mapinfo->height - 1));
}

int	check_grid(t_mapinfo *mapinfo)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mapinfo->height)
	{
		j = -1;
		while (++j < mapinfo->width)
		{
			if (!is_valid_map_char(mapinfo->grid[i][j]))
				return (err_msg(mapinfo->grid[i], "invalid map char", ERR_GRID));
			else if (is_player_start(mapinfo->grid[i][j]))
			{
				printf("players start = %c\n", mapinfo->grid[i][j]);
				if (mapinfo->p_start_o != '-')
					return (err_msg(NULL, "dup player start position", ERR_GRID));
				mapinfo->p_start_x = j;
				mapinfo->p_start_y = i;
				mapinfo->p_start_o = mapinfo->grid[i][j];
			}
		}
	}
	if (!is_valid_player_pos(mapinfo))
		return (err_msg(NULL, "invalid player position", ERR_GRID));
	return (SUCCESS);
}