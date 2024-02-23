/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:20:00 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/23 14:20:00 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_mapinfo(t_mapinfo *info)
{
	info->rawdata = NULL;
	info->map = NULL;
	info->map_bgn = NULL;
	info->grid = NULL;
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
	info->p_start_o = '-';
	info->p_start_x = 0;
	info->p_start_y = 0;
}

void	free_mapinfo(t_mapinfo	*info)
{
	if (info->rawdata != NULL)
		free(info->rawdata);
	if (info->map != NULL)
		free_array(info->map);
	if (info->grid != NULL)
		free_array(info->grid);
	if (info->map_bgn != NULL)
		free(info->map_bgn);
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
	
	//free additional elements?
}