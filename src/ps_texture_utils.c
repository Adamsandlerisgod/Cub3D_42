/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:55 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/23 18:54:07 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

//check texture type & paths/color codes
int	is_valid_texture_type(char *mapdir)
{
	const char	*valid_directions[] = {"NO", "SO", "EA", "WE", "C", "F"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(mapdir, valid_directions[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//color codes
int	is_valid_color_code(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (0);
		i++;
	}
	if (ft_atoi(color) > 255)
		return (0);
	return (1);
}

// int	rgb_to_int(char **rgb)
// {
// 	char **color;
// 	int
// 	color = ft_split(rgb, ',');
// 	return (ft_atoi(color[0]) << 16) | (ft_atoi(color[1]) << 8) | ft_atoi(color[2]);
// }

int	is_valid_texture_path(char type, char *path)
{
	int		fd;
	int		i;
	char	**color;

	fd = open(path, O_RDONLY);
	if (type == 'N' || type == 'S' || type == 'E' || type == 'W')
	{
		if (fd == -1)
			return (err_msg(path, strerror(errno), FAILURE));
		close(fd);
	}
	else if (type == 'F' || type == 'C')
	{
		color = ft_split(path, ','); //split colors
		if (count_array_elements(color) != 3)	//check for 3 values
		{
			free_array(color);
			return (err_msg(path, "invalid floor/ceiling color info", FAILURE));
		}
		i = 0;
		while (i < 3)
		{
			if (!is_valid_color_code(color[i]))
			{
				free_array(color);
				return (err_msg(path, "invalid color code", FAILURE));
			}
			i++;
		}
		free_array(color);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	is_duplicate_type(t_mapinfo *info, char type)
{
	return ((type == 'N' && info->no_path)
		|| (type == 'S' && info->so_path)
		|| (type == 'W' && info->we_path)
		|| (type == 'E' && info->ea_path)
		|| (type == 'F' && info->f_color_str)
		|| (type == 'C' && info->c_color_str));
}