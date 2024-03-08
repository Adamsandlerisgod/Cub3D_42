/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:57:19 by justindaly        #+#    #+#             */
/*   Updated: 2024/03/07 18:58:43 by whendrik         ###   ########.fr       */
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

int	check_grid(t_mapinfo *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->height)
	{
		j = -1;
		while (++j < info->width)
		{
			if (!is_valid_map_char(info->grid[i][j]))
				return (err_msg(info->grid[i], "invalid map char", ERR_GRID));
			else if (is_player_start(info->grid[i][j]))
			{
				if (info->p_start_o != '-')
					return (err_msg(NULL, "dup player start pos", ERR_GRID));
				info->p_start_x = j;
				info->p_start_y = i;
				info->p_start_o = info->grid[i][j];
			}
		}
	}
	if (!is_valid_player_pos(info))
		return (err_msg(NULL, "invalid player position", ERR_GRID));
	info->grid[info->p_start_y][info->p_start_x] = '0';
	return (SUCCESS);
}
