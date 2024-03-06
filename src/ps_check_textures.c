/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:48:41 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 20:54:31 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

//fill mapinfo struct
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
		info->f_color_str = ft_strdup(path);
		// info->f_color_str = rgb_to_int(path);
		//convert color to int;
	else if (type == 'C')
		info->c_color_str = ft_strdup(path);
		//convert color to int
	return (SUCCESS);
}

int	get_texture_info(t_mapinfo *mapinfo, char *line)
{
	char	**texture_data;

	texture_data = ft_split(line, ' ');
	if (count_array_elements(texture_data) != 2)
	{
		free_array(texture_data);
		return (err_msg(line, "invalid texture line", ERR_INFO));
	}
	if (!is_valid_texture_type(texture_data[0]))
	{
		free_array(texture_data);
		return (err_msg(line, "invalid texture type", ERR_INFO));
	}
	if (is_valid_texture_path(texture_data[0][0], texture_data[1])) //check if the texture paths are valid
	{
		free_array(texture_data);
		return (ERR_INFO);
	}
	if (is_duplicate_type(mapinfo, texture_data[0][0])) //check for duplicates
	{
		free_array(texture_data);
		return (err_msg(line, "duplicate type", ERR_INFO));
	}
	// printf("FILLING INFO...\n");
	fill_mapinfo_struct(mapinfo, texture_data[0][0], texture_data[1]);//set paths in mapinfo struct
	// printf("INFO FILLED!\n");
	free_array(texture_data);
	return (0);
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
		if (get_texture_info(m_info, lines[i]) == ERR_INFO) 		//check texture data
			return (free_array(lines), ERR_INFO);
		i++;
		if (m_info->no_path && m_info->so_path && m_info->ea_path && m_info->we_path && m_info->c_color_str && m_info->f_color_str) //break if all textures (NO, SO, EA, WE, C, F) found
		{
			printf("all texture info found!\n");
			break ;
		}
	}
	if (lines[i] == NULL)
		return (free_array(lines), err_msg(NULL, "no map in file", ERR_INFO));
	else if (lines[i] != NULL) // check if there is more data after texture info
		m_info->map_bgn = ft_strdup(lines[i]); //set first line of map
	create_map_array(m_info, lines, i); //create 2D MAP ARRAY
	print_array(lines);
	free_array(lines);
	return (0);
}
