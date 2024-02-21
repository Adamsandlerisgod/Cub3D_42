/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cubfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:03:33 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/21 19:31:23 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

//check 1
char	*get_raw(char *file)
{
	int 	fd;
	int		bytes;
	char	*result;

	result = (char *)malloc(sizeof(char) * MAX_MAPSIZE);
	if (!result)
		return (err_msg(NULL, "malloc error", FAILURE), NULL);
	fd = open(file, O_RDONLY);
	bytes = read(fd, result, MAX_MAPSIZE);
	if (bytes < 0)
		return (free(result), err_msg(file, "unable to read", FAILURE), NULL);
	if (bytes == 0)
		return (free(result), err_msg(file, "is empty", FAILURE), NULL);
	result[bytes] = '\0';
	return (result);
}

int	count_array_elements(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	//array = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

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
	return ((type == 'N' && info->no_path) || 
		(type == 'S' && info->so_path) ||
		(type == 'W' && info->we_path) ||
		(type == 'E' && info->ea_path) ||
		(type == 'F' && info->fl_color) ||
		(type == 'C' && info->ce_color));

}

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
		info->fl_color = ft_strdup(path);
		//convert color to int;
	else if (type == 'C')
		info->ce_color = ft_strdup(path);
		//convert color to int
	return (SUCCESS);
}

int	get_texture_info(t_mapinfo *mapinfo, char *line)
{
	char **texture_data;

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
		if (m_info->no_path && m_info->so_path && m_info->ea_path && m_info->we_path && m_info->ce_color && m_info->fl_color) //break if all textures (NO, SO, EA, WE, C, F) found
		{
			printf("all texture info found!\n");
			break;
		}
	}
	if (lines[i] != NULL) // check if there is more data after texture info
		m_info->map_bgn = ft_strdup(lines[i]);//set first line of map
	create_map_array(m_info, lines, i); //create 2D MAP ARRAY
	free_array(lines);
	return (0);
}

int	validate_cub(int argc, char **argv, t_mapinfo *m_info)
{
	if (argc != 2)
		return (err_msg("Usage", "./cub3d <path_to_map.cub>", 1));
	if (check_file(argv[1]) == FAILURE)
		return (ERR_ARG);
	printf("checked file\n");
	init_mapinfo(m_info);
	print_mapinfo(m_info);
	printf("reading map...\n");
	m_info->rawdata = get_raw(argv[1]);
	if (!m_info->rawdata)
		return (ERR_FILE);
	printf("mapinfo->raw:\n%s\n-------------------\n", m_info->rawdata);
	//check 2: extract texture info, check all info is there
	if (check_texture_info(m_info) == ERR_INFO)
		return (free_mapinfo(m_info), ERR_INFO);
	print_mapinfo(m_info);
	//validate map
	
	return (0);
}