/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_floodfill_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:58:11 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 17:01:39 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	is_fillable_up(t_mapinfo *mapinfo, int x, int y)
{
	return (mapinfo->flood[y - 1][x] != '1' && mapinfo->flood[y - 1][x] != '*');
}

int	is_fillable_down(t_mapinfo *mapinfo, int x, int y)
{
	return (mapinfo->flood[y + 1][x] != '1' && mapinfo->flood[y + 1][x] != '*');
}

int	is_fillable_right(t_mapinfo *mapinfo, int x, int y)
{
	return (mapinfo->flood[y][x + 1] != '1' && mapinfo->flood[y][x + 1] != '*');
}

int	is_fillable_left(t_mapinfo *mapinfo, int x, int y)
{
	return (mapinfo->flood[y][x - 1] != '1' && mapinfo->flood[y][x - 1] != '*');
}
