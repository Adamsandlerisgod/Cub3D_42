/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:48:41 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 16:43:40 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

/* convert rgb string to rgb int */
void	rgb_to_int(int *value, char *rgb)
{
	char	**color;

	color = ft_split(rgb, ',');
	*value = (ft_atoi(color[0]) << 16) | (ft_atoi(color[1]) << 8)
		| ft_atoi(color[2]);
	free_array(color);
}

/* fill mapinfo struct data */
int	fill_mapinfo_struct(t_mapinfo *info, char type, char *path)
{
	if (type == 'N')
		info->no_path = ft_strdup(path);
	else if (type == 'S')
		info->so_path = ft_strdup(path);
	else if (type == 'E')
		info->ea_path = ft_strdup(path);
	else if (type == 'W')
		info->we_path = ft_strdup(path);
	else if (type == 'F')
	{
		info->f_color_str = ft_strdup(path);
		rgb_to_int(&info->f_color_int, path);
	}
	else if (type == 'C')
	{
		info->c_color_str = ft_strdup(path);
		rgb_to_int(&info->c_color_int, path);
	}
	return (SUCCESS);
}

int	get_texture_info(t_mapinfo *mapinfo, char *line)
{
	char	**t_data;

	t_data = ft_split(line, ' ');
	if (count_array_elements(t_data) != 2)
		return (free_array(t_data), err_msg(line, "texture line", ERR_INFO));
	if (!is_valid_texture_type(t_data[0]))
		return (free_array(t_data), err_msg(line, "texture type", ERR_INFO));
	if (is_valid_texture_path(t_data[0][0], t_data[1]))
		return (free_array(t_data), ERR_INFO);
	if (is_duplicate_type(mapinfo, t_data[0][0]))
		return (free_array(t_data), err_msg(line, "duplicate type", ERR_INFO));
	fill_mapinfo_struct(mapinfo, t_data[0][0], t_data[1]);
	free_array(t_data);
	return (SUCCESS);
}

void	create_map_array(t_mapinfo *info, char **lines, int i)
{
	int		bgn;
	int		map_length;
	char	**map;
	int		j;

	bgn = i;
	map_length = 0;
	while (lines[i])
	{
		map_length++;
		i++;
	}
	i = bgn;
	map = malloc(sizeof(char *) * (map_length + 1));
	j = 0;
	while (j < map_length)
	{
		map[j] = ft_strdup(lines[i]);
		i++;
		j++;
	}
	map[j] = NULL;
	info->map = map;
}

int	check_texture_info(t_mapinfo *m_info)
{
	char	**lines;
	int		i;

	lines = ft_split(m_info->rawdata, '\n');
	i = 0;
	while (lines[i])
	{
		if (get_texture_info(m_info, lines[i]) == ERR_INFO)
			return (free_array(lines), ERR_INFO);
		i++;
		if (m_info->no_path && m_info->so_path && m_info->ea_path
			&& m_info->we_path && m_info->c_color_str && m_info->f_color_str)
		{
			printf("all texture info found!\n");
			break ;
		}
	}
	if (lines[i] == NULL)
		return (free_array(lines), err_msg(NULL, "no map in file", ERR_INFO));
	else if (lines[i] != NULL)
		m_info->map_bgn = ft_strdup(lines[i]);
	create_map_array(m_info, lines, i);
	print_array(lines);
	free_array(lines);
	return (0);
}
