/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:02:27 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 17:01:33 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

char	**dup_array(char **array)
{
	int		i;
	int		size;
	char	**dup;

	if (array == NULL)
		return (NULL);
	size = count_array_elements(array);
	dup = malloc(sizeof(char *) * (size + 1));
	if (!dup)
		err_msg(NULL, "malloc error", EXIT_FAILURE);
	i = 0;
	while (array[i])
	{
		dup[i] = ft_strdup(array[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	check_map_border(t_mapinfo *info, int x, int y)
{
	if (x == 0 || x == (info->width - 1) || y == 0 || y == (info->height - 1))
		info->closed = FALSE;
}

void	flood_fill(t_mapinfo *info, int x, int y)
{
	if (info->closed == FALSE)
		return ;
	info->flood[y][x] = '*';
	if (is_fillable_up(info, x, y))
	{
		check_map_border(info, x, y - 1);
		flood_fill(info, x, y - 1);
	}
	if (is_fillable_down(info, x, y))
	{
		check_map_border(info, x, y + 1);
		flood_fill(info, x, y + 1);
	}
	if (is_fillable_right(info, x, y))
	{
		check_map_border(info, x + 1, y);
		flood_fill(info, x + 1, y);
	}
	if (is_fillable_left(info, x, y))
	{
		check_map_border(info, x - 1, y);
		flood_fill(info, x - 1, y);
	}
}

int	check_walls(t_mapinfo *mapinfo)
{
	if (!(mapinfo->width > 2 && mapinfo->height > 2))
		return (err_msg(NULL, "invalid map size", ERR_WALL));
	mapinfo->flood = dup_array(mapinfo->grid);
	flood_fill(mapinfo, mapinfo->p_start_x, mapinfo->p_start_y);
	if (mapinfo->closed == FALSE)
		return (err_msg(NULL, "map not closed by wall", ERR_WALL));
	return (SUCCESS);
}
