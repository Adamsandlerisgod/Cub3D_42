/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_texture_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:30:07 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 19:30:55 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	is_duplicate_type(t_mapinfo *info, char type)
{
	return ((type == 'N' && info->no_path)
		|| (type == 'S' && info->so_path)
		|| (type == 'W' && info->we_path)
		|| (type == 'E' && info->ea_path)
		|| (type == 'F' && info->f_color_str)
		|| (type == 'C' && info->c_color_str));
}