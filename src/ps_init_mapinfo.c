/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_mapinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:20:00 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/23 19:28:03 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_mapinfo(t_mapinfo *info)
{
	info->rawdata = NULL;
	info->map_bgn = NULL;
	info->map = NULL;
	info->grid = NULL;
	info->flood = NULL;
	info->closed = TRUE;
	info->width = 0;
	info->height = 0;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->f_color_str = NULL;
	info->c_color_str = NULL;
	info->f_color_int = 0;
	info->c_color_int = 0;
	info->p_start_x = 0;
	info->p_start_y = 0;
	info->p_start_o = '-';
}

void	free_mapinfo(t_mapinfo	*info)
{
	if (info->rawdata != NULL)
		free(info->rawdata);
	if (info->map_bgn != NULL)
		free(info->map_bgn);
	if (info->map != NULL)
		free_array(info->map);
	if (info->grid != NULL)
		free_array(info->grid);
	if (info->flood != NULL)
		free_array(info->flood);
	if (info->no_path != NULL)
		free(info->no_path);
	if (info->so_path != NULL)
		free(info->so_path);
	if (info->we_path != NULL)
		free(info->we_path);
	if (info->ea_path != NULL)
		free(info->ea_path);
	if (info->f_color_str != NULL)
		free(info->f_color_str);
	if (info->c_color_str != NULL)
		free(info->c_color_str);
}
