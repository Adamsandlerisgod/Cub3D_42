/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:20:00 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/21 19:58:51 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_mapinfo(t_mapinfo *info)
{
	info->rawdata = NULL;
	info->map = NULL;
	info->map_bgn = NULL;
	info->width = 0;
	info->height = 0;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->fl_color = NULL;
	info->ce_color = NULL;
	info->f_color = 0;
	info->c_color = 0;
	info->p_start_o = '-';
	info->p_start_x = 0;
	info->p_start_y = 0;
}

void	free_mapinfo(t_mapinfo	*info)
{
	if (info->rawdata != NULL)
		free(info->rawdata);
	// if (info->map != NULL)
	// 	//free_array(info->map);
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
	if (info->fl_color != NULL)
		free(info->fl_color);
	if (info->ce_color != NULL)
		free(info->ce_color);
	
	//free additional elements?
}