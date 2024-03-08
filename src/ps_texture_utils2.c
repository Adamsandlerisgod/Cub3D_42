/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_texture_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:30:07 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/08 20:45:52 by whendrik         ###   ########.fr       */
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

int	check_size(t_mapinfo *info)
{
	if (info->height > 65 || info->width > 90)
		return (err_msg(NULL, "map too large", ERR_GRID));
	return (SUCCESS);
}
